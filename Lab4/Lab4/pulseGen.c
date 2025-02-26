#include <avr/io.h>
#include <stdint.h>
#include "pulsegen.h"
#include "writeBit.h"
#include "TinyTimber.h"

// setPulse() togglar utg�ngen och schemal�gger n�sta toggling (halvperiod).
int setPulse(Pulsegenerator *self, int arg) {
	// Om frekvens=0, s�tt porten l�g och sluta toggla.
	if (self->frec == 0) {
		self->pos = false;
		int packed = PACK_BIT(self->bit, 0);
		SYNC(self->wbitPtr, writeBit, packed);
		return 0;
	}
	
	// Annars toggla pos (true/false => bit=1/0).
	self->pos = !(self->pos);
	int value = self->pos ? 1 : 0;
	int packed = PACK_BIT(self->bit, value);
	// Skriv ut p� PORTE via SYNC f�r att v�nta tills skrivningen �r klar.
	SYNC(self->wbitPtr, writeBit, packed);
	
	// Delay = 500 / frekvens => halvperiod i ms, AFTER planerar n�sta anrop.
	int delay = 500 / self->frec;
	AFTER(MSEC(delay), self, setPulse, 0);
	return 0;
}

// getFrec() returnerar aktuell frekvens.
int getFrec(Pulsegenerator *self, int arg) {
	return self->frec;
}

// FrecInc() �kar frekvensen upp till max 99.
// Om frekvens gick fr�n 0 till >0, starta togglingen via ASYNC(setPulse).
int FrecInc(Pulsegenerator *self, int arg) {
	int wasZero = (self->frec == 0);
	if (self->frec < 99) {
		self->frec++;
		if (wasZero && self->frec > 0) {
			ASYNC(self, setPulse, 0);
		}
	}
	return self->frec;
}

// FrecDec() minskar frekvensen ned till minst 0 (stannar togglingen om den blir 0).
int FrecDec(Pulsegenerator *self, int arg) {
	if (self->frec > 0) {
		self->frec--;
	}
	return self->frec;
}

// FrecReset() v�xlar om frekvens=0 => �terst�ll gammal frekvens,
// annars spara nuvarande i frec_old, nollst�ll frec, s�tt utg�ng l�g.
int FrecReset(Pulsegenerator *self, int arg) {
	if (self->frec == 0) {
		self->frec = self->frec_old;
		if (self->frec > 0) {
			ASYNC(self, setPulse, 0);
		}
		} else {
		self->frec_old = self->frec;
		self->frec = 0;
		self->pos = false;
		int packed = PACK_BIT(self->bit, 0);
		SYNC(self->wbitPtr, writeBit, packed);
	}
	return 0;
}
