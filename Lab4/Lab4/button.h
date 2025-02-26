#ifndef BUTTON_H_
#define BUTTON_H_

#include "GUI.h"
#include "TinyTimber.h"

// Dessa makron l�ser av knapparna genom att kolla om motsvarande pin
// �r l�g (knapp nertryckt).
#define PRESSEDUP   (!( (PINB >> 6) & 0x01 ))
#define PRESSEDDN   (!( (PINB >> 7) & 0x01 ))
#define PRESSEDLT   (!( (PINE >> 2) & 0x01 ))
#define PRESSEDRT   (!( (PINE >> 3) & 0x01 ))
#define PRESSEDCN   (!( (PINB >> 4) & 0x01 ))

// Button-struktur, inneh�ller en GUI-pekare f�r att kunna anropa GUI-funktioner
// (t.ex. att byta generator eller uppdatera frekvens).
typedef struct {
	Object super;
	GUI *gui;
	// H�r beh�vs ingen lastPressTime eftersom vi k�r AFTER-baserad debounce.
} Button;

// Initieringsmakro f�r Button, d�r man kopplar ett GUI-objekt.
#define initButton(gui_ptr) { initObject(), gui_ptr }

// Prototyper f�r knappfunktioner.
int checkButtons(Button *this, int arg);
int debounceButtons(Button *this, int arg);

int leftdir(Button *this, int arg);
int rightdir(Button *this, int arg);
int updir(Button *this, int arg);
int downdir(Button *this, int arg);
int centerdir(Button *this, int arg);

#endif /* BUTTON_H_ */
