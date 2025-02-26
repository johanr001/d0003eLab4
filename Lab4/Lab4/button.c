#include "button.h"
#include "TinyTimber.h"
#include "pulsegen.h"
#include "GUI.h"
#include <avr/io.h>

// btn_init() sätter upp ingångar med pull-ups och aktiverar pin change interrupts.
// Detta gör att knapptryckningar kan generera avbrott och anropa checkButtons.
void btn_init(){
	// Aktivera intern pull-up på PB7, PB6, PB4 samt PE3, PE2.
	PORTB |= (1<<PB7) | (1<<PB6) | (1<<PB4);
	PORTE |= (1<<PE3) | (1<<PE2);
	
	// Slå på pin change interrupts för PCIE1, PCIE0.
	EIMSK |= (1<<PCIE1) | (1<<PCIE0);
	
	// Masker för vilka pinnar som ska övervakas av PCINT0 och PCINT1.
	PCMSK0 |= (1<<PCINT3) | (1<<PCINT2);
	PCMSK1 |= (1<<PCINT15) | (1<<PCINT14) | (1<<PCINT12);
}

// checkButtons() anropas när en pin change interrupt sker.
// I stället för att direkt läsa och reagera, använder vi AFTER(50ms) för debounce.
// Det innebär att koden väntar 50 ms innan knapptrycket analyseras, för att undvika studs.
int checkButtons(Button *this, int arg) {
	// AFTER schemalägger att debounceButtons ska köras om 50 ms.
	// ASYNC eller SYNC vore för direkt anrop, men AFTER används för fördröjning/debounce.
	AFTER(MSEC(50), this, debounceButtons, 0);
	return 0;
}

// debounceButtons() körs 50 ms senare, vilket ger knappen tid att stabilisera sig
// (mindre risk för studs). Därefter kollar vi vilka knappar som faktiskt är nedtryckta
// och anropar motsvarande funktion.
int debounceButtons(Button *this, int arg) {
	if (PRESSEDLT) {
		leftdir(this, 0);
	}
	if (PRESSEDRT) {
		rightdir(this, 0);
	}
	if (PRESSEDUP) {
		updir(this, 0);
	}
	if (PRESSEDDN) {
		downdir(this, 0);
	}
	if (PRESSEDCN) {
		centerdir(this, 0);
	}
	return 0;
}

// Nedanstående funktioner kollar återigen om knappen fortfarande är nedtryckt
// (så att man inte kör vidare om den hann släppas).
// De använder ASYNC för att starta en metod i en annan "tråd" (d.v.s.
// i TinyTimbers schemaläggning) utan att blockera denna knappkod.

// leftdir => anropar switchGen(0) för att välja "vänster" generator, om PRESSEDLT är sant.
int leftdir(Button *this, int arg) {
	if (PRESSEDLT) {
		ASYNC(this->gui, switchGen, 0);
	}
	return 0;
}

// rightdir => anropar switchGen(1) för "höger" generator.
int rightdir(Button *this, int arg) {
	if (PRESSEDRT) {
		ASYNC(this->gui, switchGen, 1);
	}
	return 0;
}

// updir => anropar guiFrecInc() för att öka frekvensen.
int updir(Button *this, int arg) {
	if (PRESSEDUP) {
		ASYNC(this->gui, guiFrecInc, 0);
	}
	return 0;
}

// downdir => anropar guiFrecDec() för att minska frekvensen.
int downdir(Button *this, int arg) {
	if (PRESSEDDN) {
		ASYNC(this->gui, guiFrecDec, 0);
	}
	return 0;
}

// centerdir => anropar guiFrecReset() för att växla mellan lagrad/återställd frekvens.
int centerdir(Button *this, int arg) {
	if (PRESSEDCN) {
		ASYNC(this->gui, guiFrecReset, 0);
	}
	return 0;
}
