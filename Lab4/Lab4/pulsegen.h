/*
 * pulsegen.h
 *
 * Created: 2025-02-21 09:28:04
 *  Author: Amadeus
 */ 

#include <avr/io.h>

#include <stdint.h>

#include <stdbool.h>

#include "TinyTimber.h"

#ifndef PULSE_H_
#define PULSE_H_

typedef struct {
	Object super;
	
	uint16_t frec;
	
	uint16_t frec_old;
	
	bool pos;
	
	uint16_t *reg;
	
	
} Pulsegenerator;

#define initPulse(frec, frec_old, pos, reg) { initObject(), 0, frec, frec_old, pos. reg }
#define uint16_t getFrec(Pulsegenerator *this, uint16_t frec){}
#define uint16_t FrecInc(Pulsegenerator *this, uint16_t frec){}
#define uint16_t FrecDec(Pulsegenerator *this, uint16_t frec){}
#define void FrecReset(Pulsegenerator *this, uint16_t frec, uint16_t frec_old){}

#endif /* PULSE_H_ */