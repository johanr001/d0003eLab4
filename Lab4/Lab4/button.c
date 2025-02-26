#include "button.h"
#include "TinyTimber.h"
#include "pulsegen.h"
#include "GUI.h"
#include <avr/io.h>

// btn_init() s�tter upp ing�ngar med pull-ups och aktiverar pin change interrupts.
// Detta g�r att knapptryckningar kan generera avbrott och anropa checkButtons.
void btn_init(){
	// Aktivera intern pull-up p� PB7, PB6, PB4 samt PE3, PE2.
	PORTB |= (1<<PB7) | (1<<PB6) | (1<<PB4);
	PORTE |= (1<<PE3) | (1<<PE2);
	
	// Sl� p� pin change interrupts f�r PCIE1, PCIE0.
	EIMSK |= (1<<PCIE1) | (1<<PCIE0);
	
	// Masker f�r vilka pinnar som ska �vervakas av PCINT0 och PCINT1.
	PCMSK0 |= (1<<PCINT3) | (1<<PCINT2);
	PCMSK1 |= (1<<PCINT15) | (1<<PCINT14) | (1<<PCINT12);
}

// checkButtons() anropas n�r en pin change interrupt sker.
// I st�llet f�r att direkt l�sa och reagera, anv�nder vi AFTER(50ms) f�r debounce.
// Det inneb�r att koden v�ntar 50 ms innan knapptrycket analyseras, f�r att undvika studs.
int checkButtons(Button *this, int arg) {
	// AFTER schemal�gger att debounceButtons ska k�ras om 50 ms.
	// ASYNC eller SYNC vore f�r direkt anrop, men AFTER anv�nds f�r f�rdr�jning/debounce.
	AFTER(MSEC(50), this, debounceButtons, 0);
	return 0;
}

// debounceButtons() k�rs 50 ms senare, vilket ger knappen tid att stabilisera sig
// (mindre risk f�r studs). D�refter kollar vi vilka knappar som faktiskt �r nedtryckta
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

// Nedanst�ende funktioner kollar �terigen om knappen fortfarande �r nedtryckt
// (s� att man inte k�r vidare om den hann sl�ppas).
// De anv�nder ASYNC f�r att starta en metod i en annan "tr�d" (d.v.s.
// i TinyTimbers schemal�ggning) utan att blockera denna knappkod.

// leftdir => anropar switchGen(0) f�r att v�lja "v�nster" generator, om PRESSEDLT �r sant.
int leftdir(Button *this, int arg) {
	if (PRESSEDLT) {
		ASYNC(this->gui, switchGen, 0);
	}
	return 0;
}

// rightdir => anropar switchGen(1) f�r "h�ger" generator.
int rightdir(Button *this, int arg) {
	if (PRESSEDRT) {
		ASYNC(this->gui, switchGen, 1);
	}
	return 0;
}

// updir => anropar guiFrecInc() f�r att �ka frekvensen.
int updir(Button *this, int arg) {
	if (PRESSEDUP) {
		ASYNC(this->gui, guiFrecInc, 0);
	}
	return 0;
}

// downdir => anropar guiFrecDec() f�r att minska frekvensen.
int downdir(Button *this, int arg) {
	if (PRESSEDDN) {
		ASYNC(this->gui, guiFrecDec, 0);
	}
	return 0;
}

// centerdir => anropar guiFrecReset() f�r att v�xla mellan lagrad/�terst�lld frekvens.
int centerdir(Button *this, int arg) {
	if (PRESSEDCN) {
		ASYNC(this->gui, guiFrecReset, 0);
	}
	return 0;
}
