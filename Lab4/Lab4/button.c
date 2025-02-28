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


// HoldcheckerUp() checkar om den h�ller.
int holdCheckerUp(Button *self, int arg) {
	if (self->held == +1 && PRESSEDUP) {
		ASYNC(self->gui, guiFrecInc, 0);
		AFTER(MSEC(100), self, holdCheckerUp, 0);

	}
	return 0;
}

int holdCheckerDown(Button *self, int arg) {
	if (self->held == -1 && PRESSEDDN) {
		ASYNC(self->gui, guiFrecDec, 0);
		AFTER(MSEC(100), self, holdCheckerDown, 0);

	}
	return 0;
}
	
int buttonCheckerLR(Button *self, int arg) {
	if (PRESSEDLT) {
		leftdir(self,0);
	}
	if (PRESSEDRT) {
		rightdir(self,0);
	}
	return 0;
}

// buttonChecker() checkar vilken knapp som blivit tryckt.
int buttonCheckerUDC(Button *self, int arg) {
	if (PRESSEDUP) {
		updir(self, 0);
	} 
	else if (PRESSEDDN) {
		downdir(self, 0);
	} 
	else {
		self->held = 0;  // Reset n�r inte upp eller ner
	}
	
	if (PRESSEDCN) {
		centerdir(self, 0);
	}
	return 0;
}

// leftdir() => anropar switchGen(0) f�r att v�lja "v�nster" generator.
int leftdir(Button *self, int arg) {
	if (PRESSEDLT) {
		ASYNC(self->gui, switchGen, 0);
	}
	return 0;
}

// rightdir() => anropar switchGen(1) f�r "h�ger" generator.
int rightdir(Button *self, int arg) {
	if (PRESSEDRT) {
		ASYNC(self->gui, switchGen, 1);
	}
	return 0;
}

// updir() => anropar guiFrecInc() f�r att �ka frekvensen.
int updir(Button *self, int arg) {
	if (PRESSEDUP && self->held == 0) { // Checka om knappen �r nerclickad och inte held. Annars spamclick g�r snabbare scroll.
		self->held = +1; // S�tt held till +1
		ASYNC(self->gui, guiFrecInc, 0); // �ka frekvensen
		AFTER(MSEC(500),self, holdCheckerUp, 0); // Starta holdCheckerUp() funktionen f�r att repetera
	}
	return 0;
}

// downdir() => anropar guiFrecDec() f�r att minska frekvensen.
int downdir(Button *self, int arg) {
    if (PRESSEDDN && self->held == 0) { // Checka om knappen �r nerclickad och inte held. Annars spamclick g�r snabbare scroll.
	    self->held = -1; // S�tt held till true
	    ASYNC(self->gui, guiFrecDec, 0); // Minska frekvensen
	    AFTER(MSEC(500),self, holdCheckerDown, 0); // Starta holdCheckerDown() funktionen f�r att repetera
    }
	return 0;
}

// centerdir() => anropar guiFrecReset() f�r att v�xla mellan lagrad/�terst�lld frekvens.
int centerdir(Button *self, int arg) {
	if (PRESSEDCN) {
		AFTER(MSEC(100),self->gui, guiFrecReset, 0);
	}
	return 0;
}
