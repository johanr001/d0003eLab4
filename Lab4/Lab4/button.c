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


// HoldcheckerUp() kontrollerar om knappen hålls nere och fortsätter att öka frekvensen.
int holdCheckerUp(Button *self, int arg) {
	if (!self->holdUpRunning) { // Om funktionen inte körs, avsluta
		return 0;
	}
	if (self->holdUpRunning && PRESSEDUP) { // Om knappen fortfarande hålls nere
		ASYNC(self->gui, guiFrecInc, 0); // Öka frekvensen
		AFTER(MSEC(100), self, holdCheckerUp, 0); // En ny körning efter 1000ms
	}
	else { // Om knappen har släppts, avsluta håll-funktionen
		self->holdUpRunning = false;
	}
	return 0;
}

// HoldcheckerDown() kontrollerar om knappen hålls nere och fortsätter att minska frekvensen.
int holdCheckerDown(Button *self, int arg) {
	if (!self->holdDownRunning) { // Om funktionen inte körs, avsluta
		return 0;
	}
	if (self->holdDownRunning && PRESSEDDN) { // Om knappen fortfarande hålls nere
		ASYNC(self->gui, guiFrecDec, 0); // Minska frekvensen
		AFTER(MSEC(100), self, holdCheckerDown, 0); // En ny körning efter 1000ms
	}
	else { // Om knappen har släppts, sätt Running till false.
		self->holdDownRunning = false;
	}
	return 0;
}

// buttonCheckerLR() kontrollerar om vänster eller höger knappen har blivit tryckt.
int buttonCheckerLR(Button *self, int arg) {
	if (PRESSEDLT) {
		leftdir(self, 0);
	}
	if (PRESSEDRT) {
		rightdir(self, 0);
	}
	return 0;
}


// buttonCheckerUDC() kontrollerar om upp, ner eller center knappen har blivit tryckt.
int buttonCheckerUDC(Button *self, int arg) {
	if (PRESSEDUP) {
		updir(self, 0);
	}
	else {
		self->heldUp = false; // Om knappen inte är nedtryckt, sätt heldUp till False
	}
	if (PRESSEDDN) {
		downdir(self, 0); // Hantera ner-knappen
	}
	else {
		self->heldDown = false; // Om knappen inte är nedtryckt, sätt heldDown till False
	}
	if (PRESSEDCN) {
		centerdir(self, 0);
	}
	return 0;
}

// leftdir() => anropar switchGen(0) för att välja vänster generator.
int leftdir(Button *self, int arg) {
	if (PRESSEDLT) {
		ASYNC(self->gui, switchGen, 0);
	}
	return 0;
}

// rightdir() => anropar switchGen(1) för höger generator.
int rightdir(Button *self, int arg) {
	if (PRESSEDRT) {
		ASYNC(self->gui, switchGen, 1);
	}
	return 0;
}

// updir() => anropar guiFrecInc() för att öka frekvensen.
int updir(Button *self, int arg) {
	// Kontrollera om "UP" är nedtryckt och inte redan held
	if (PRESSEDUP && !self->heldUp) {
		self->heldUp = true; // Markera att knappen hålls nere
		ASYNC(self->gui, guiFrecInc, 0); // Öka frekvensen direkt vid första trycket
		if (!self->holdUpRunning) { // Checka om hold funktionen redan körs
			self->holdUpRunning = true;
			AFTER(MSEC(500), self, holdCheckerUp, 0); // Starta holdCheckerUp efter 500ms
		}
	}
	else if (!PRESSEDUP) { // När knappen släpps, återställ flaggan
		self->heldUp = false;
	}
	return 0;
}

// downdir() => anropar guiFrecDec() för att minska frekvensen.
int downdir(Button *self, int arg) {
	// Kontrollera om "DOWN" är nedtryckt och inte redan held
	if (PRESSEDDN && !self->heldDown) {
		self->heldDown = true; // Markera att knappen hålls nere
		ASYNC(self->gui, guiFrecDec, 0); // Minska frekvensen direkt vid första trycket
		if (!self->holdDownRunning) { // Kontrollera om hold funktionen redan körs
			self->holdDownRunning = true;
			AFTER(MSEC(500), self, holdCheckerDown, 0); // Starta holdCheckerDown efter 500ms
		}
	}
	else if (!PRESSEDDN) { // När knappen släpps, återställ flaggan
		self->heldDown = false;
	}
	return 0;
}
// centerdir() => anropar guiFrecReset() för att växla mellan lagrad/återställd frekvens.
int centerdir(Button *self, int arg) {
	if (PRESSEDCN) {
		AFTER(MSEC(100),self->gui, guiFrecReset, 0);
	}
	return 0;
}
