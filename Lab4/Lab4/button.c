/*
 * button.c
 *
 * Created: 21/02/2025 08:51:58
 *  Author: johan_csf2sgl
 */ 

#include <avr/io.h>
#include "button.h"
#include "pulsegen.h"
#include "GUI.h"

void btn_init(){
	
	//PORTB |= (1 << PB7);  // Pull up resistor på PB7

	PORTB|= (1<<PB7) | (1<<PB6) | (1<<PB4);
	PORTE|= (1<<PE3) | (1<<PE2);
	EIMSK|= (1<<PCIE1) | (1<<PCIE0);
	PCMSK0|= (1<<PCINT3) | (1<<PCINT2);
	PCMSK1|= (1<<PCINT15) | (1<<PCINT14) | (1<<PCINT12);
	
}


static volatile bool has_released = true;

void leftdir(Button *this, uint8_t midPos ) {
	if (PRESSEDLT & midPos = 0){
		ASYNC(switchGen(this, midPos))
		
	}
}

void rightdir(Button *this, uint8_t midPos ) {
	if (PRESSEDRT & midPos = 1){
		ASYNC(switchGen(this, midPos))	
	}	
}

void updir(Button *this, uint16_t frec ) {
	if (PRESSEDUP){
		ASYNC(FrecInc(this,frec))
	}

}

void downdir(Button *this, uint16_t frec ) {
	if (PRESSEDDN){
		ASYNC(FrecDec(this,frec))	
	}	
}

void centerdir(Button *this, uint16_t frec ) {
	if (PRESSEDCN){
		ASYNC(FrecReset(this,frec))
	}	
}