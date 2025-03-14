#include <avr/io.h>
#include <stdint.h>
#include "pulsegen.h"
#include "writeBit.h"
#include "TinyTimber.h"

// setPulse() togglar utg�ngen och schemal�gger n�sta toggling.
int setPulse(Pulsegenerator *self, int arg) {
	// Om frekvens=0, s�tt porten l�g och sluta toggla.
    if (self->frec == 0) {
	    ASYNC(self->wbit, writeBit, 0);
		AFTER(MSEC(1000), self, setPulse, 0);
    }
	else {
		// Annars toggla outputHigh.
		ASYNC(self->wbit, toggleBit, 0);
		
		// Delay = 1000 / frekvens => period i ms, AFTER planerar n�sta anrop.
		int delay = 500 / self->frec;
		AFTER(MSEC(delay), self, setPulse, 0);
	}
	return 0;
}

// getFrec() returnerar aktuell frekvens.
int getFrec(Pulsegenerator *self, int arg) {
	return self->frec;
}

// FrecInc() �kar frekvensen upp till max 99.
int FrecInc(Pulsegenerator *self, int arg) {
    unsigned char old = self->frec;
    if (self->frec < 99) {
	    self->frec++;
    }
    return 0;
}


// FrecDec() minskar frekvensen ned till minst 0 (stoppa togglingen om den blir 0).
int FrecDec(Pulsegenerator *self, int arg) {
	if (self->frec > 0) {
		self->frec--;
	}
	return 0;
}

// FrecReset() v�xlar om frekvens=0 => �terst�ll gammal frekvens,
// annars spara nuvarande i frec_old, nollst�ll frec, s�tt output low.
int FrecReset(Pulsegenerator *self, int arg) {
    if (self->frec == 0) {
	    self->frec = self->frec_old;
	    } 
	else {
	    self->frec_old = self->frec;
	    self->frec = 0;
	    ASYNC(self->wbit, writeBit, 0);
    }
    return 0;
}