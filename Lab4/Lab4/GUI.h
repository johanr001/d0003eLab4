/*
 * GUI.h
 *
 * Created: 2025-02-21 09:27:08
 *  Author: Amadeus
 */ 


#include <avr/io.h>

#include <stdint.h>

#include <stdbool.h>

#include "TinyTimber.h"

#ifndef GUI_H_
#define GUI_H_

typedef struct {
	Object super;
	
	uint8_t midPos;
	
	

} GUI;

#define initGUI(midPos) { initObject(), 0, midPos }
#define void switchGen(GUI *this, uint8_t midPos){}

#endif /* GUI_H_ */