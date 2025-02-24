/*
 * button.c
 *
 * Created: 21/02/2025 08:51:58
 *  Author: johan_csf2sgl
 */ 

#include <avr/io.h>

void btn_init(){
	
	//PORTB |= (1 << PB7);  // Pull up resistor på PB7

	PORTB|= (1<<PB7) | (1<<PB6) | (1<<PB4);
	PORTE|= (1<<PE3) | (1<<PE2);
	EIMSK|= (1<<PCIE1) | (1<<PCIE0);
	PCMSK0|= (1<<PCINT3) | (1<<PCINT2);
	PCMSK1|= (1<<PCINT15) | (1<<PCINT14) | (1<<PCINT12);
	
}