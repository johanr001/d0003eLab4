
#include <avr/io.h>

#include "TinyTimber.h"

#include "button.h"

#include "interruptHandler.h"

int horizontal(Interrupthandler *self, int arg) {
	ASYNC(self->button, buttonCheckerLR, 0);
	return 0;
}

int vertandcent(Interrupthandler *self, int arg) {
	ASYNC(self->button, buttonCheckerUDC, 0);
	return 0;
}