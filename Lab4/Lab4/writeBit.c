#include "writeBit.h"
#include <avr/io.h>
#include "TinyTimber.h"

// writeBit() s�tter eller rensar angiven bit i PORTE.
// 'arg' �r ett packat heltal, d�r h�gbyte=bitnummer, l�gbyte=0/1.
int writeBit(Writebit *this, int arg) {
	uint8_t bit = (arg >> 8) & 0xFF;
	uint8_t value = arg & 0xFF;
	if (value)
	PORTE |= (1 << bit);
	else
	PORTE &= ~(1 << bit);
	return 0;
}

// toggleBit() v�nder bit i PORTE motsvarande this->portBit.
// Anv�nds om man vill v�xla till/fr�n 1 (ex. en LED).
int toggleBit(Writebit *this, int arg) {
	PORTE ^= (1 << this->portBit);
	return 0;
}
