/*
 * writeBit.c
 *
 * Created: 24/02/2025 11:39:04
 *  Author: johan_csf2sgl
 */ 

#include "writeBit.h"

#include <avr/io.h>

#include <stdint.h>

#include "TinyTimber.h"

void toggleBit(Writebit *this, uint8_t portBit){
	
	PORTE ^= (1 << this->portBit);
	
		
}