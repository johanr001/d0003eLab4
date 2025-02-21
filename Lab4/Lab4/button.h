/*
 * button.h
 *
 * Created: 2025-02-21 09:27:26
 *  Author: Amadeus
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

typedef struct {
	Object super;

} Button;

#define initCounter(en) { initObject(), 0, en }

#endif /* BUTTON_H_ */