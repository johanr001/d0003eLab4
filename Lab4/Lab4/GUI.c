#include "GUI.h"
#include "TinyTimber.h"
#include "pulsegen.h"
#include <avr/io.h>
#include <stdint.h>

// font[] inneh�ller bitm�nster f�r siffrorna 0-9 p� LCD:n.
// Varje siffra representeras som ett 16-bitars v�rde.
const uint16_t font[] = {
	0x1551, // 0
	0x0110, // 1
	0x1E11, // 2
	0x1B11, // 3
	0x0B50, // 4
	0x1B41, // 5
	0x1F41, // 6
	0x0111, // 7
	0x1F51, // 8
	0x1B51  // 9
};



// Starta LCD
void lcd_init() {
	// LCD Control Register A:
	// Turn on LCD (LCDEN = 1)
	// Low Power Waveform (LCDAB = 1)
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);

	// LCD Control Register B:
	// Asynchronous Clock (LCDCS = 1)
	// 1/3 Bias (LCD2B = 0)
	// 1/4 Duty (LCDMUX1 & LCDMUX0 = 1)
	// 25 Segments (LCDPM2 & LCDPM1 & LCDPM0 = 1)
	// Prescaler N = 16 (LCDPS2 & LCDPS1 & LCDPS0 = 0)
	// Clock Divide = 8 (LCDCD2 & LCDCD1 & LCDCD0 = 1
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) |
	(1 << LCDPM1) | (1 << LCDPM0) | (1 << LCDCD2) | (1 << LCDCD1) |
	(1 << LCDCD0);

	// LCD Contrast Control Register:
	// Drive Time = 300 �s (LCDDC2 & LCDDC1 & LCDDC0 = 0)
	// Contrast Control Vol	tage = 3.35 V (LCDCC3 & LCDCC2 & LCDCC1 & LCDCC0 = 1)
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
}

// Karakt�r (allts� 0-9) f�r positionen 0-5
void writeChar(char ch, int pos) {
	if (pos < 0 || pos > 5) return;                     // Checka att position �r korrekt.
	uint16_t segments = 0x0000;   // Default �r tom.
	if (ch >= '0' && ch <= '9') { // Checka om det �r siffra
		segments = font[ch - '0'];	// H�mta font data f�r siffra array positionen, allts� t.ex
		// ASCII f�r 8 blir till: 56-48=8. Och font[8] = 0x1F51.
	}
	uint8_t *base = (uint8_t *)&LCDDR0 + pos / 2; // Ber�kna basregistret f�r positionen. Displayen anv�nder LCDDR0-LCDDR19. *base dereference pointer till minnesadressen av korrekt. L�s sida 8 av butterfly_lcd. De �r i par. S� pos = 0,1 blir LCDDR0 Type cast ocks� ifall det inte fungerar annars kan testa utan det fungerar s�kert. Ber�kna offset allts� low eller high nibble f�r registret om den �r j�mn eller oj�mn. pos = 0,2,4 blir till 0 offset.
	int offset = (pos % 2) * 4;

	base[0] = (base[0] & ~(0xF << offset)) | ((segments & 0xF) << offset);			// Uppdatera nibble i f�rsta registret
	base[5] = (base[5] & ~(0xF << offset)) | (((segments >> 4) & 0xF) << offset);		// Uppdatera nibble i LCDDRx+5 registret, allts� pointer offset med base[5].
	base[10] = (base[10] & ~(0xF << offset)) | (((segments >> 8) & 0xF) << offset);	// Om offset 4 till exempel. 00001111 blir till 11110000, sedan 00001111, och bitwise AND vilket g�r de 4 bits som har best�mts med offset till 0000.
	base[15] = (base[15] & ~(0xF << offset)) | (((segments >> 12) & 0xF) << offset);	// Sedan segments & 0xF blir 000000000000xxxx, AND med segments ger bara v�rdet f�r dessa 4 bits. Samma fast f�r offset f�r de andra raderna. Allts� om vi har aaaabbbbccccdddd, s� ger varje rad, dddd,cccc,bbbb,aaaa. Sedan << offset f�r att flytta v�nster om det beh�vs. Sedan | OR f�r att kombinera med h�lften tom och h�lften redan fylld. Allts� 0000xxxx om ingen offset, eller xxxx0000 om offset.
}

void printAt(long num, int pos) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
	
}


// switchGen() byter vilken generator (left=0, right=1) som �r aktiv.
// Om redan r�tt generator �r vald, g�r inget. Annars uppdatera midPos och kalla updateDisplay.
int switchGen(GUI *self, int arg) {
	if (self->midPos == arg) {
		// Om samma generator redan �r aktiv, g�r inget.
	}
	self->midPos = arg;
	// Anv�nder ASYNC f�r att anropa updateDisplay()
	ASYNC(self, updateDisplay, 0);
	return 0;
}

// updateDisplay() h�mtar generatorernas frekvenser
// och visar dem p� LCD. Mittpositionen visar vilken som �r aktiv.
int updateDisplay(GUI *self, int arg) {
	// V�nstra sidan: frekvens f�r gen1
	printAt((SYNC(self->gen1, getFrec, 0)), 0);

	// H�gra sidan: frekvens f�r gen2
	printAt((SYNC(self->gen2, getFrec, 0)), 4);
	// Mitten: visa vilken generator som �r aktiv, visar "10" om gen1 �r vald, "01" om gen2 �r vald.
	if (self->midPos == 0) {
		printAt(10, 2);
		} else {
		printAt(1, 2);
	}
	return 0;
}

// guiFrecInc() �kar frekvensen f�r den aktiva generatorn via ASYNC,
// och anropar sedan updateDisplay f�r att visa den nya frekvensen.
int guiFrecInc(GUI *self, int arg) {
	if (self->midPos == 0) {
		ASYNC(self->gen1, FrecInc, 0);
		} else {
		ASYNC(self->gen2, FrecInc, 0);
	}
	ASYNC(self, updateDisplay, 0);
	return 0;

}

// guiFrecDec() minskar frekvensen f�r den aktiva generatorn,
// sedan uppdateras displayen.
int guiFrecDec(GUI *self, int arg) {
	if (self->midPos == 0) {
		ASYNC(self->gen1, FrecDec, 0);
		} else {
		ASYNC(self->gen2, FrecDec, 0);
	}
	ASYNC(self, updateDisplay, 0);
	return 0;
}

// guiFrecReset() v�xlar mellan lagrad och nuvarande frekvens.
// Efter�t uppdateras displayen f�r att visa f�r�ndringen.
int guiFrecReset(GUI *self, int arg) {
	if (self->midPos == 0) {
		ASYNC(self->gen1, FrecReset, 0);
		} else {
		ASYNC(self->gen2, FrecReset, 0);
	}
	ASYNC(self, updateDisplay, 0);
	return 0;
}

// startProgram() k�rs vid uppstart. Den startar genereringen av pulser
// och anropar updateDisplay vid start.
int startProgram(GUI *self) {
	// Starta b�da pulsgeneratorerna direkt (ASYNC s� att vi inte blockerar).
	ASYNC(self->gen1, setPulse, 0);
	ASYNC(self->gen2, setPulse, 0);

	// Uppdatera displayen omedelbart s� vi ser initialfrekvenser (0).
	ASYNC(self, updateDisplay, 0);
	
	return 0;
}