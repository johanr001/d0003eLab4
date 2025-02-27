#include "writeBit.h"
#include <avr/io.h>
#include "TinyTimber.h"

// writeBit() sätter eller rensar angiven bit i PORTE.
int writeBit(Writebit *self, int value) {
	if (value)
	PORTE |= (1 << self->portBit);
	else
	PORTE &= ~(1 << self->portBit);
	return 0;
}

// toggleBit() vänder bit i PORTE motsvarande self->portBit.
int toggleBit(Writebit *self, int arg) {
	PORTE ^= (1 << self->portBit);
	return 0;
}
