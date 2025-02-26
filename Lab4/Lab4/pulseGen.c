#include <avr/io.h>
#include <stdint.h>
#include "pulsegen.h"
#include "writeBit.h"
#include "TinyTimber.h"

// setPulse() togglar utg�ngen och schemal�gger n�sta toggling (halvperiod).
int setPulse(Pulsegenerator *this, int arg) {
	// Om frekvens=0, s�tt porten l�g och sluta toggla.
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
	// Skriv ut p� PORTE via SYNC f�r att v�nta tills skrivningen �r klar.
	SYNC(this->wbitPtr, writeBit, packed);
	
	// Delay = 500 / frekvens => halvperiod i ms, AFTER planerar n�sta anrop.
	int delay = 500 / this->frec;
	AFTER(MSEC(delay), this, setPulse, 0);
	return 0;
}

// getFrec() returnerar aktuell frekvens.
int getFrec(Pulsegenerator *this, int arg) {
	return this->frec;
}

// FrecInc() �kar frekvensen upp till max 99.
// Om frekvens gick fr�n 0 till >0, starta togglingen via ASYNC(setPulse).
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

// FrecReset() v�xlar om frekvens=0 => �terst�ll gammal frekvens,
// annars spara nuvarande i frec_old, nollst�ll frec, s�tt utg�ng l�g.
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
