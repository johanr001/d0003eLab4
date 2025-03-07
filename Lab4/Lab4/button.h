#ifndef BUTTON_H_
#define BUTTON_H_

#include "GUI.h"
#include "TinyTimber.h"
#include <stdbool.h>

#define PRESSEDUP   (!( (PINB >> 6) & 0x01 ))
#define PRESSEDDN   (!( (PINB >> 7) & 0x01 ))
#define PRESSEDLT   (!( (PINE >> 2) & 0x01 ))
#define PRESSEDRT   (!( (PINE >> 3) & 0x01 ))
#define PRESSEDCN   (!( (PINB >> 4) & 0x01 ))

// Button-struct, innehåller en GUI-pekare för att kunna anropa GUI-funktioner
typedef struct {
	Object super;
	GUI *gui;
	bool heldUp; // Checkar om "UP" är nedtryckt.
	bool heldDown; // Checkar om "DOWN" är nedtryckt.
	bool holdUpRunning; // Checkar om HoldUp funktion är running, så vi inte får extra om man clickar snabbt. Då får vi flera scrolls som kör samtidigt.
	bool holdDownRunning; // Checkar om HoldUp funktion är running, så vi inte får extra om man clickar snabbt. Då får vi flera scrolls som kör samtidigt.
	bool heldCenter;
} Button;


#define initButton(gui) { initObject(), gui, 0, 0, 0, 0, 0 }

void btn_init();

int buttonCheckerLR(Button *self, int arg);
int buttonCheckerUDC(Button *self, int arg);
int holdCheckerUp(Button *self, int arg);
int holdCheckerDown(Button *self, int arg);

int leftdir(Button *self, int arg);
int rightdir(Button *self, int arg);
int updir(Button *self, int arg);
int downdir(Button *self, int arg);
int centerdir(Button *self, int arg);

#endif /* BUTTON_H_ */
