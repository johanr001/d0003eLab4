#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"
#include "pulsegen.h"

// GUI-objektet innehåller pekare till två pulsgeneratorer (gen1, gen2)
// och variabeln midPos.
typedef struct {
	Object super;
	Pulsegenerator *gen1;
	Pulsegenerator *gen2;
	bool midPos;
} GUI;


#define initGUI(p1, p2) { initObject(), p1, p2, 0 }


int switchGen(GUI *self, int arg);
int updateDisplay(GUI *self, int arg);
int guiFrecInc(GUI *self, int arg);
int guiFrecDec(GUI *self, int arg);
int guiFrecReset(GUI *self, int arg);

void lcd_init(void);
void writeChar(char ch, int pos);
void printAt(long num, int pos);

#endif /* GUI_H_ */
