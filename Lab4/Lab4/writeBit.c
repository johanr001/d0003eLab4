#include "writeBit.h"
#include <avr/io.h>
#include "TinyTimber.h"

// writeBit() sätter eller rensar angiven bit i PORTE.
// 'arg' är ett packat heltal, där högbyte=bitnummer, lågbyte=0/1.
int writeBit(Writebit *this, int arg) {
	uint8_t bit = (arg >> 8) & 0xFF;
	uint8_t value = arg & 0xFF;
	if (value)
	PORTE |= (1 << bit);
	else
	PORTE &= ~(1 << bit);
	return 0;
}

// toggleBit() vänder bit i PORTE motsvarande this->portBit.
// Används om man vill växla till/från 1 (ex. en LED).
int toggleBit(Writebit *this, int arg) {
	PORTE ^= (1 << this->portBit);
	return 0;
}
