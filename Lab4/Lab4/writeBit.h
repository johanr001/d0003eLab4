#ifndef WRITEBIT_H_
#define WRITEBIT_H_

#include <avr/io.h>
#include <stdint.h>
#include "TinyTimber.h"

// Writebit-objekt kan skriva eller toggla en viss bit i PORTE.
// portBit lagras men anv�nds fr�mst i toggleBit.
typedef struct {
	Object super;   // �rver fr�n TinyTimber Object
	uint8_t portBit;
} Writebit;

// initWbit() initierar ett Writebit-objekt med en given bitnummer.
#define initWbit(portBit) { initObject(), portBit }

// writeBit() skriver 0 eller 1 till en bit i PORTE (argumentet packar bit och v�rde).
// toggleBit() v�nder bit i PORTE baserat p� portBit.
int writeBit(Writebit *this, int arg);
int toggleBit(Writebit *this, int arg);

#endif /* WRITEBIT_H_ */
