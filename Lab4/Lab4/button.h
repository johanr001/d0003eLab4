/*
 * button.h
 *
 * Created: 2025-02-21 09:27:26
 *  Author: Amadeus
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "GUI.h"

typedef struct {
	Object super;
	GUI midPos;
} Button;

#define initButton(en) { initObject(), 0, en }

#define PRESSEDUP (!( (PINB >> 6) & 0x01 ))
#define PRESSEDDN (!( (PINB >> 7) & 0x01 ))
#define PRESSEDLT (!( (PINE >> 2) & 0x01 ))
#define PRESSEDRT (!( (PINE >> 3) & 0x01 ))
#define PRESSEDCN (!( (PINB >> 4) & 0x01 ))

#endif /* BUTTON_H_ */