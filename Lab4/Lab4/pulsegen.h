#ifndef PULSE_H_
#define PULSE_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "writeBit.h"

// Pulsegenerator genererar pulser på en vald bit i PORTE.
typedef struct {
	Object super;   // Ärver från Object för TinyTimber
	unsigned char frec;  // Aktuell frekvens
	unsigned char frec_old; // Sparad frekvens
	bool outputHigh;       // true => hög output, false => låg
	Writebit *wbitPtr; // Pekare till Writebit-objekt för att skriva bitar
} Pulsegenerator;


#define initPulse(wbitPtr) { initObject(), 0, 0, false, wbitPtr }

int setPulse(Pulsegenerator *self, int arg); // Toucha inte dehär,
int getFrec(Pulsegenerator *self, int arg);  // de använder 
int FrecInc(Pulsegenerator *self, int arg);  // antingen kernel primitives
int FrecDec(Pulsegenerator *self, int arg); // eller så crossar de
int FrecReset(Pulsegenerator *self, int arg); // object boundary.

#endif /* PULSE_H_ */
