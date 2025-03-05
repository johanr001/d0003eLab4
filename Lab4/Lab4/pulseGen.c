#include <avr/io.h>
#include <stdint.h>
#include "pulsegen.h"
#include "writeBit.h"
#include "TinyTimber.h"

// setPulse() togglar utgången och schemalägger nästa toggling.
int setPulse(Pulsegenerator *self, int arg) {
	// Om frekvens=0, sätt porten låg och sluta toggla.
    if (self->frec == 0) {
	    ASYNC(self->wbit, writeBit, 0);
		self->pulseActive = false;
	    return 0;
    }
	
	// Inom setPulse callar vi med arg 1, så arg == 0 är utanför denna funktion.
    if (arg == 0) { // Om den är utanför,
	    if (self->pulseActive) { // Om den redan är aktiv returna bara,
		    return 0;
	    }
	    self->pulseActive = true; // Om den inte är aktiv, sätt den till aktiv och fortsätt
    } // Sedan kommer SetPulse, 1 after att skippa denna check eftersom den passar arg = 1.
	
	// Annars toggla outputHigh.
    ASYNC(self->wbit, toggleBit, 0);
	
	// Delay = 1000 / frekvens => period i ms, AFTER planerar nästa anrop.
    int delay = 1000 / self->frec;
    AFTER(MSEC(delay), self, setPulse, 1);
    return 0;
}

// getFrec() returnerar aktuell frekvens.
int getFrec(Pulsegenerator *self, int arg) {
	return self->frec;
}

// FrecInc() ökar frekvensen upp till max 99.
int FrecInc(Pulsegenerator *self, int arg) {
    unsigned char old = self->frec;
    if (self->frec < 99) {
	    self->frec++;
    }
    // Om går från 0 till mer än 0 starta.
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

// FrecReset() växlar om frekvens=0 => återställ gammal frekvens,
// annars spara nuvarande i frec_old, nollställ frec, sätt output low.
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