#include <avr/io.h>
#include <stdint.h>
#include "pulsegen.h"
#include "writeBit.h"
#include "TinyTimber.h"

// setPulse() togglar utgången och schemalägger nästa toggling (halvperiod).
int setPulse(Pulsegenerator *this, int arg) {
	// Om frekvens=0, sätt porten låg och sluta toggla.
	if (this->frec == 0) {
		this->pos = false;
		int packed = PACK_BIT(this->bit, 0);
		SYNC(this->wbitPtr, writeBit, packed);
		return 0;
	}
	
	// Annars toggla pos (true/false => bit=1/0).
	this->pos = !(this->pos);
	int value = this->pos ? 1 : 0;
	int packed = PACK_BIT(this->bit, value);
	// Skriv ut på PORTE via SYNC för att vänta tills skrivningen är klar.
	SYNC(this->wbitPtr, writeBit, packed);
	
	// Delay = 500 / frekvens => halvperiod i ms, AFTER planerar nästa anrop.
	int delay = 500 / this->frec;
	AFTER(MSEC(delay), this, setPulse, 0);
	return 0;
}

// getFrec() returnerar aktuell frekvens.
int getFrec(Pulsegenerator *this, int arg) {
	return this->frec;
}

// FrecInc() ökar frekvensen upp till max 99.
// Om frekvens gick från 0 till >0, starta togglingen via ASYNC(setPulse).
int FrecInc(Pulsegenerator *this, int arg) {
	int wasZero = (this->frec == 0);
	if (this->frec < 99) {
		this->frec++;
		if (wasZero && this->frec > 0) {
			ASYNC(this, setPulse, 0);
		}
	}
	return this->frec;
}

// FrecDec() minskar frekvensen ned till minst 0 (stannar togglingen om den blir 0).
int FrecDec(Pulsegenerator *this, int arg) {
	if (this->frec > 0) {
		this->frec--;
	}
	return this->frec;
}

// FrecReset() växlar om frekvens=0 => återställ gammal frekvens,
// annars spara nuvarande i frec_old, nollställ frec, sätt utgång låg.
int FrecReset(Pulsegenerator *this, int arg) {
	if (this->frec == 0) {
		this->frec = this->frec_old;
		if (this->frec > 0) {
			ASYNC(this, setPulse, 0);
		}
		} else {
		this->frec_old = this->frec;
		this->frec = 0;
		this->pos = false;
		int packed = PACK_BIT(this->bit, 0);
		SYNC(this->wbitPtr, writeBit, packed);
	}
	return 0;
}
