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
	uint16_t frec;  // Aktuell frekvens
	uint16_t frec_old; // Sparad frekvens
	bool outputHigh;       // true => hög output, false => låg
	Writebit *wbitPtr; // Pekare till Writebit-objekt för att skriva bitar
} Pulsegenerator;


#define initPulse(portBit, frec, wbitPtr) { initObject(), frec, 0, false, wbitPtr }

int setPulse(Pulsegenerator *self, int arg);
int getFrec(Pulsegenerator *self, int arg);
int FrecInc(Pulsegenerator *self, int arg);
int FrecDec(Pulsegenerator *self, int arg);
int FrecReset(Pulsegenerator *self, int arg);

#endif /* PULSE_H_ */
