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
	    return 0;
    }
	// Annars toggla outputHigh (true/false => bit=1/0).
    ASYNC(self->wbit, toggleBit, 0);
	
	// Delay = 1000 / frekvens => period i ms, AFTER planerar n�sta anrop.
    int delay = 1000 / self->frec;
    AFTER(MSEC(delay), self, setPulse, 0);
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
    // Om g�r fr�n 0 till mer �n 0 starta.
    if (old == 0 && self->frec > 0) {
	    ASYNC(self, setPulse, 0);
    }
    return self->frec;
    }


// FrecDec() minskar frekvensen ned till minst 0 (stoppa togglingen om den blir 0).
int FrecDec(Pulsegenerator *self, int arg) {
	if (self->frec > 0) {
		self->frec--;
	}
	return self->frec;
}

// FrecReset() v�xlar om frekvens=0 => �terst�ll gammal frekvens,
// annars spara nuvarande i frec_old, nollst�ll frec, s�tt output low.
int FrecReset(Pulsegenerator *self, int arg) {
    if (self->frec == 0) {
	    self->frec = self->frec_old;
	    if (self->frec > 0) {
		    ASYNC(self, setPulse, 0);
	    }
	    } else {
	    self->frec_old = self->frec;
	    self->frec = 0;
	    ASYNC(self->wbit, writeBit, 0);
    }
    return 0;
    }