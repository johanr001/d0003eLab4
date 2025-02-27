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


// buttonChecker() checkar vilken knapp som blivit tryckt.
int buttonCheckerLR(Button *self, int arg) {
	if (PRESSEDLT) {
		leftdir(self, 0);
	}
	if (PRESSEDRT) {
		rightdir(self, 0);
	}
	return 0;
}

// buttonChecker() checkar vilken knapp som blivit tryckt.
int buttonCheckerUDC(Button *self, int arg) {
	if (PRESSEDUP) {
		updir(self, 0);
	}
	if (PRESSEDDN) {
		downdir(self, 0);
	}
	if (PRESSEDCN) {
		centerdir(self, 0);
	}
	return 0;
}

// leftdir() => anropar switchGen(0) för att välja "vänster" generator, om PRESSEDLT är sant.
int leftdir(Button *self, int arg) {
	if (PRESSEDLT) {
		ASYNC(self->gui, switchGen, 0);
	}
	return 0;
}

// rightdir() => anropar switchGen(1) för "höger" generator.
int rightdir(Button *self, int arg) {
	if (PRESSEDRT) {
		ASYNC(self->gui, switchGen, 1);
	}
	return 0;
}

// updir() => anropar guiFrecInc() för att öka frekvensen.
int updir(Button *self, int arg) {
	if (PRESSEDUP) {
		ASYNC(self->gui, guiFrecInc, 0);
	}
	return 0;
}

// downdir() => anropar guiFrecDec() för att minska frekvensen.
int downdir(Button *self, int arg) {
	if (PRESSEDDN) {
		ASYNC(self->gui, guiFrecDec, 0);
	}
	return 0;
}

// centerdir() => anropar guiFrecReset() för att växla mellan lagrad/återställd frekvens.
int centerdir(Button *self, int arg) {
	if (PRESSEDCN) {
		ASYNC(self->gui, guiFrecReset, 0);
	}
	return 0;
}
