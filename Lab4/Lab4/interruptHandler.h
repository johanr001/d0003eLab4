#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "TinyTimber.h"
#include "button.h"

typedef struct{

	Object super;

	Button *button;	
	
} Interrupthandler;

#define initInterruptHandler(button) { initObject(), button}

int horizontal(Interrupthandler *self, int arg);
int vertandcent(Interrupthandler *self, int arg);

#endif /* INTERRUPTHANDLER_H_ */