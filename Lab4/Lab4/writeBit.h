#ifndef WRITEBIT_H_
#define WRITEBIT_H_

#include <avr/io.h>
#include <stdint.h>
#include "TinyTimber.h"

// Writebit-objekt kan skriva eller toggla en viss bit i PORTE.
typedef struct {
	Object super;
	uint8_t portBit;
} Writebit;

#define initWbit(portBit) { initObject(), portBit }

int writeBit(Writebit *self, int arg);
int toggleBit(Writebit *self, int arg);

#endif /* WRITEBIT_H_ */
