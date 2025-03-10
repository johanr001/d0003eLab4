#include "writeBit.h"


// writeBit() s�tter eller rensar angiven bit i PORTE.
int writeBit(Writebit *self, int arg) {
	if (arg)
	PORTE |= (1 << self->portBit);
	else
	PORTE &= ~(1 << self->portBit);
	return 0;
}

// toggleBit() v�nder bit i PORTE motsvarande self->portBit.
int toggleBit(Writebit *self, int arg) {
	PORTE ^= (1 << self->portBit);
	return 0;
}
