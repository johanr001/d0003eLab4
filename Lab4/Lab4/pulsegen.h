#ifndef PULSE_H_
#define PULSE_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "writeBit.h"

// Pulsegenerator genererar pulser på en vald bit i PORTE.
// frec (0..99) anger hur snabb toggling (0 => avstängd).
typedef struct {
	Object super;   // Ärver från Object för TinyTimber
	uint16_t frec;  // Aktuell frekvens
	uint16_t frec_old; // Sparad frekvens
	bool pos;       // true => hög output, false => låg
	uint8_t bit;    // Vilken bit i PORTE som ska togglas
	Writebit *wbitPtr; // Pekare till Writebit-objekt för att skriva bitar
} Pulsegenerator;

// initPulse makro initierar objektet.
// PACK_BIT är en hjälpmakro för att packa (bit,val) i en int.
#define initPulse(bit, freq, wbitPointer) { initObject(), freq, 0, false, bit, wbitPointer }
#define PACK_BIT(bit, value) (((bit) << 8) | ((value) & 0xFF))

// Metoder som en pulsgenerator stödjer:
// setPulse togglar utgång, getFrec returnerar frekvens,
// FrecInc/Ded/Reset justerar frekvens.
int setPulse(Pulsegenerator *self, int arg);
int getFrec(Pulsegenerator *self, int arg);
int FrecInc(Pulsegenerator *self, int arg);
int FrecDec(Pulsegenerator *self, int arg);
int FrecReset(Pulsegenerator *self, int arg);

#endif /* PULSE_H_ */
