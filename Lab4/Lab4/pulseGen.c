/*
 * pulsegen.c
 *
 * Created: 21/02/2025 08:40:38
 *  Author: johan_csf2sgl
 */ 

#include <avr/io.h>

#include <stdint.h>

#include "pulsegen.h"

#include "TinyTimber.h"

uint16_t getFrec(Pulsegenerator *this, uint16_t frec){
	
	
	
	return this->frec;
}

uint16_t FrecInc(Pulsegenerator *this, uint16_t frec){
	
	(this->frec)++;
	printAt(pos,frec)
}

uint16_t FrecDec(Pulsegenerator *this, uint16_t frec){
	
	
	
	(this->frec)--;
}

void FrecReset(Pulsegenerator *this, uint16_t frec, uint16_t frec_old){
	
	this->frec_old=this->frec;
	
	this->frec=0;
}

void setPulse(Pulsegenerator *this, uint16_t frec){
	// SKAPA PULSER PÅ PORTEN SOM VI SKICKAR IN MED WRITEBIT OCH PORTBIT PARAMETER & ARGUMENT

