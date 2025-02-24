/*
 * writeBit.h
 *
 * Created: 24/02/2025 11:39:30
 *  Author: johan_csf2sgl
 */ 

#include <avr/io.h>

#include <stdint.h>

#include "TinyTimber.h"

#ifndef WRITEBIT_H_
#define WRITEBIT_H_

typedef struct {
	
	Object super;
	
	uint8_t portBit;
	
	
	
	
} Writebit;

#define initWbit(portBit) { initObject(), 0, portBit }


#endif /* WRITEBIT_H_ */