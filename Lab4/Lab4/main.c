#include "TinyTimber.h"
#include "pulsegen.h"
#include "GUI.h"
#include "button.h"
#include "avr_init.h"
#include "writeBit.h"

// Skapar ett Writebit-objekt f�r att kunna skriva/ta bort 1-bitar i PORTE.
Writebit wbit = initWbit(0);

// Skapar tv� pulsgeneratorer (pulseGen1, pulseGen2) som styr bit 4 och bit 6 i PORTE.
// De f�r en pekare till wbit s� att de kan anropa writeBit-funktioner.
Pulsegenerator pulseGen1 = initPulse(4, 0, &wbit);
Pulsegenerator pulseGen2 = initPulse(6, 0, &wbit);

// Skapar ett GUI-objekt som refererar b�da pulsgeneratorerna,
// f�r att kunna visa och styra deras frekvenser p� LCD.
GUI gui = initGUI(&pulseGen1, &pulseGen2);

// Skapar ett Button-objekt som kopplas till GUI f�r att byta generator/frekvens.
Button button = initButton(&gui);

// startApp() k�rs vid uppstart. Den startar genereringen av pulser
// och anropar updateDisplay asynkront f�r att initiera LCD-uppdateringar.
int startProgram(GUI *self, int arg) {
	// Starta b�da pulsgeneratorerna direkt (ASYNC s� att vi inte blockerar).
	ASYNC(&pulseGen1, setPulse, 0);
	ASYNC(&pulseGen2, setPulse, 0);

	// Uppdatera displayen omedelbart s� vi ser initialfrekvenser (0).
	ASYNC(self, updateDisplay, 0);

	return 0;
}

int main(void) {
	// Initiera timer/klocka via avr_init().
	avr_init();
	
	// Initiera LCD innan vi b�rjar skriva ut.
	lcd_init();
	
	// Initiera knappar (pullups + pin change interrupt).
	btn_init();

	// Installera knappobjektet som avbrottshanterare f�r PCINT0 och PCINT1.
	INSTALL(&button, checkButtons, IRQ_PCINT0);
	INSTALL(&button, checkButtons, IRQ_PCINT1);

	// TINYTIMBER startar k�rnan. Vi anropar startApp p� gui som f�rsta metod.
	return TINYTIMBER(&gui, startProgram, 0);
}
