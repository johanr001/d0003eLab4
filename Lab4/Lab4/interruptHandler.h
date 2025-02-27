/*
 * interruptHandler.h
 *
 * Created: 27/02/2025 10:30:12
 *  Author: johan_csf2sgl
 */ 

#include "TinyTimber.h"

#include "button.h"

typedef struct{

	Object super;

	Button *button;	
	
} Interrupthandler;


#ifndef INTERRUPTHANDLER_H_
#define initInterr(btn) { initObject(), btn}

	void horizontal(Interrupthandler *self, int arg);
	void vertical(Interrupthandler *self, int arg);	


#endif /* INTERRUPTHANDLER_H_ */