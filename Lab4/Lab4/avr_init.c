#include <avr/io.h>
#include "avr_init.h"

// avr_init() initierar klockan, timer1, prescalers etc.
void avr_init(){
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	DDRB &= ~(1 << DDB7); // PB7 som input (S�tt till DDB7 till 0)
	PORTB |= (1 << PB7);  // Pull up resistor p� PB7
	
	TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
	
	TCNT1 = 0;
	
	TIMSK1 |= (1 << OCIE1A);
	OCR1A=194; //f_oCnA = (f_clk_I/O)/(2*N*(1+OCRnA) 194 eller 3905 f�r en sekund
};
