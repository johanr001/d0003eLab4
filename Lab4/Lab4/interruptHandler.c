/*
 * interruptHandler.c
 *
 * Created: 27/02/2025 10:29:50
 *  Author: johan_csf2sgl
 */ 

#include <avr/io.h>

#include "TinyTimber.h"

#include "button.h"

#include "interruptHandler.h"

void horizontal(Interrupthandler *self, int arg) {
	
	ASYNC(self->button, buttonCheckerLR, 0);
	
}

void vertical(Interrupthandler *self, int arg) {
	
	ASYNC(self->button, buttonCheckerUDC, 0);
	
}