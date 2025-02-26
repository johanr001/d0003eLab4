#ifndef PULSE_H_
#define PULSE_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "writeBit.h"

// Pulsegenerator genererar pulser p� en vald bit i PORTE.
// frec (0..99) anger hur snabb toggling (0 => avst�ngd).
typedef struct {
	Object super;   // �rver fr�n Object f�r TinyTimber
	uint16_t frec;  // Aktuell frekvens
	uint16_t frec_old; // Sparad frekvens
	bool pos;       // true => h�g output, false => l�g
	uint8_t bit;    // Vilken bit i PORTE som ska togglas
	Writebit *wbitPtr; // Pekare till Writebit-objekt f�r att skriva bitar
} Pulsegenerator;

// initPulse makro initierar objektet.
// PACK_BIT �r en hj�lpmakro f�r att packa (bit,val) i en int.
#define initPulse(bit, freq, wbitPointer) { initObject(), freq, 0, false, bit, wbitPointer }
#define PACK_BIT(bit, value) (((bit) << 8) | ((value) & 0xFF))

// Metoder som en pulsgenerator st�djer:
// setPulse togglar utg�ng, getFrec returnerar frekvens,
// FrecInc/Ded/Reset justerar frekvens.
int setPulse(Pulsegenerator *self, int arg);
int getFrec(Pulsegenerator *self, int arg);
int FrecInc(Pulsegenerator *self, int arg);
int FrecDec(Pulsegenerator *self, int arg);
int FrecReset(Pulsegenerator *self, int arg);

#endif /* PULSE_H_ */
