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


// HoldcheckerUp() kontrollerar om knappen h�lls nere och forts�tter att �ka frekvensen.
int holdCheckerUp(Button *self, int arg) {
	if (!self->holdUpRunning) { // Om funktionen inte k�rs, avsluta
		return 0;
	}
	if (self->holdUpRunning && PRESSEDUP) { // Om knappen fortfarande h�lls nere
		SYNC(self->gui, guiFrecInc, 0); // �ka frekvensen
		AFTER(MSEC(100), self, holdCheckerUp, 0); // En ny k�rning efter 1000ms
	}
	else { // Om knappen har sl�ppts, avsluta h�ll-funktionen
		self->holdUpRunning = false;
	}
	return 0;
}

// HoldcheckerDown() kontrollerar om knappen h�lls nere och forts�tter att minska frekvensen.
int holdCheckerDown(Button *self, int arg) {
	if (!self->holdDownRunning) { // Om funktionen inte k�rs, avsluta
		return 0;
	}
	if (self->holdDownRunning && PRESSEDDN) { // Om knappen fortfarande h�lls nere
		SYNC(self->gui, guiFrecDec, 0); // Minska frekvensen
		AFTER(MSEC(100), self, holdCheckerDown, 0); // En ny k�rning efter 1000ms
	}
	else { // Om knappen har sl�ppts, s�tt Running till false.
		self->holdDownRunning = false;
	}
	return 0;
}

// buttonCheckerLR() kontrollerar om v�nster eller h�ger knappen har blivit tryckt.
int buttonCheckerLR(Button *self, int arg) {
	if (PRESSEDLT && !self->heldLeft) {
		leftdir(self, 0);
	}
	else {
		self->heldLeft = false;
	}
	if (PRESSEDRT && !self->heldRight) {
		rightdir(self, 0);
	}
	else {
		self->heldRight = false;
	}
	return 0;
}


// buttonCheckerUDC() kontrollerar om upp, ner eller center knappen har blivit tryckt.
int buttonCheckerUDC(Button *self, int arg) {
	if (PRESSEDUP && !self->heldUp) {
		updir(self, 0);
	}
	else {
		self->heldUp = false; // Om knappen inte �r nedtryckt, s�tt heldUp till False
	}
	if (PRESSEDDN && !self->heldDown) {
		downdir(self, 0); // Hantera ner-knappen
	}
	else {
		self->heldDown = false; // Om knappen inte �r nedtryckt, s�tt heldDown till False
	}
	if (PRESSEDCN && !self->heldCenter) {
		centerdir(self, 0);
	}
	else {
		self->heldCenter = false;
	}
	return 0;
}

// leftdir() => anropar switchGen(0) f�r att v�lja v�nster generator.
int leftdir(Button *self, int arg) {
	if (PRESSEDLT && !self->heldLeft) {
		self->heldLeft = true;
		SYNC(self->gui, switchGen, 0);
	}
	
	else if (!PRESSEDLT) {
		self->heldLeft = false;
	}
	return 0;
}

// rightdir() => anropar switchGen(1) f�r h�ger generator.
int rightdir(Button *self, int arg) {
	if (PRESSEDRT && !self->heldRight) {
		self->heldRight = true;
		SYNC(self->gui, switchGen, 1);
	}
	else if (!PRESSEDRT) {
		self->heldRight = false;
	}
	return 0;
}

// updir() => anropar guiFrecInc() f�r att �ka frekvensen.
int updir(Button *self, int arg) {
	// Kontrollera om "UP" �r nedtryckt och inte redan held
	if (PRESSEDUP && !self->heldUp) {
		self->heldUp = true; // Markera att knappen h�lls nere
		if (!self->holdUpRunning) { // Checka om hold funktionen redan k�rs
			self->holdUpRunning = true;
			AFTER(MSEC(50), self, holdCheckerUp, 0); // Starta holdCheckerUp efter 50ms
		}
	}
	else if (!PRESSEDUP) { // N�r knappen sl�pps, �terst�ll flaggan
		self->heldUp = false;
	}
	return 0;
}

// downdir() => anropar guiFrecDec() f�r att minska frekvensen.
int downdir(Button *self, int arg) {
	// Kontrollera om "DOWN" �r nedtryckt och inte redan held
	if (PRESSEDDN && !self->heldDown) {
		self->heldDown = true; // Markera att knappen h�lls nere
		if (!self->holdDownRunning) { // Kontrollera om hold funktionen redan k�rs
			self->holdDownRunning = true;
			AFTER(MSEC(50), self, holdCheckerDown, 0); // Starta holdCheckerDown efter 50ms
		}
	}
	else if (!PRESSEDDN) { // N�r knappen sl�pps, �terst�ll flaggan
		self->heldDown = false;
	}
	return 0;
}
// centerdir() => anropar guiFrecReset() f�r att v�xla mellan lagrad/�terst�lld frekvens.
int centerdir(Button *self, int arg) {
	if (PRESSEDCN && !self->heldCenter) {
		self->heldCenter = true;
		SYNC(self->gui, guiFrecReset, 0);
	}
	else if (!PRESSEDCN) {
		self->heldCenter = false;
	}
	return 0;
}