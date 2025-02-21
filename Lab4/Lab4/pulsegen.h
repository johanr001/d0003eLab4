/*
 * pulsegen.h
 *
 * Created: 2025-02-21 09:28:04
 *  Author: Amadeus
 */ 


#ifndef PULSE_H_
#define PULSE_H_

typedef struct {
	Object super;
	
} Pulsegenerator;

#define initCounter(en) { initObject(), 0, en }


#endif /* PULSE_H_ */