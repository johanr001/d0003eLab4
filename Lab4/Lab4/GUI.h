#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"
#include "pulsegen.h"

// GUI-objektet innehåller pekare till två pulsgeneratorer (gen1, gen2)
// samt en variabel midPos som anger vilken generator som för närvarande är "aktiv"
// (0 => generator1, 1 => generator2).
typedef struct {
	Object super;
	Pulsegenerator *gen1;
	Pulsegenerator *gen2;
	uint8_t midPos;
} GUI;

// Makro för att initiera en GUI med två pulsgeneratorer.
#define initGUI(p1, p2) { initObject(), p1, p2, 0 }

// Funktioner för att byta generator (switchGen),
// uppdatera display (updateDisplay), samt öka/minska/nollställa frekvens.
int switchGen(GUI *this, int arg);
int updateDisplay(GUI *this, int arg);
int guiFrecInc(GUI *this, int arg);
int guiFrecDec(GUI *this, int arg);
int guiFrecReset(GUI *this, int arg);

// LCD-hjälpfunktioner
void lcd_init(void);
void writeChar(char ch, int pos);
void printAt(long num, int pos);

#endif /* GUI_H_ */
