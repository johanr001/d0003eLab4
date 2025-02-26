#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"
#include "pulsegen.h"

// GUI-objektet inneh�ller pekare till tv� pulsgeneratorer (gen1, gen2)
// samt en variabel midPos som anger vilken generator som f�r n�rvarande �r "aktiv"
// (0 => generator1, 1 => generator2).
typedef struct {
	Object super;
	Pulsegenerator *gen1;
	Pulsegenerator *gen2;
	uint8_t midPos;
} GUI;

// Makro f�r att initiera en GUI med tv� pulsgeneratorer.
#define initGUI(p1, p2) { initObject(), p1, p2, 0 }

// Funktioner f�r att byta generator (switchGen),
// uppdatera display (updateDisplay), samt �ka/minska/nollst�lla frekvens.
int switchGen(GUI *this, int arg);
int updateDisplay(GUI *this, int arg);
int guiFrecInc(GUI *this, int arg);
int guiFrecDec(GUI *this, int arg);
int guiFrecReset(GUI *this, int arg);

// LCD-hj�lpfunktioner
void lcd_init(void);
void writeChar(char ch, int pos);
void printAt(long num, int pos);

#endif /* GUI_H_ */
