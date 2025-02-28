#ifndef PULSE_H_
#define PULSE_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "writeBit.h"

// Pulsegenerator genererar pulser p� en vald bit i PORTE.
typedef struct {
	Object super;   // �rver fr�n Object f�r TinyTimber
	unsigned char frec;  // Aktuell frekvens
	unsigned char frec_old; // Sparad frekvens
	bool outputHigh;       // true => h�g output, false => l�g
	Writebit *wbitPtr; // Pekare till Writebit-objekt f�r att skriva bitar
} Pulsegenerator;


#define initPulse(wbitPtr) { initObject(), 0, 0, false, wbitPtr }

int setPulse(Pulsegenerator *self, int arg); // Toucha inte deh�r,
int getFrec(Pulsegenerator *self, int arg);  // de anv�nder 
int FrecInc(Pulsegenerator *self, int arg);  // antingen kernel primitives
int FrecDec(Pulsegenerator *self, int arg); // eller s� crossar de
int FrecReset(Pulsegenerator *self, int arg); // object boundary.

#endif /* PULSE_H_ */
