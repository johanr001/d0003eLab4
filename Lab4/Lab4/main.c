#include "TinyTimber.h"
#include "pulsegen.h"
#include "GUI.h"
#include "button.h"
#include "avr_init.h"
#include "writeBit.h"
#include "interruptHandler.h"

// Skapar Writebit-objekt för att kunna skriva/ta bort 1-bitar i PORTE.
Writebit wbit4 = initWbit(4);
Writebit wbit6 = initWbit(6);


// Skapar två pulsgeneratorer (pulseGen1, pulseGen2) som styr bit 4 och bit 6 i PORTE.
// De får en pekare till wbit så att de kan anropa writeBit-funktioner.
Pulsegenerator pulseGen1 = initPulse(&wbit4);
Pulsegenerator pulseGen2 = initPulse(&wbit6);

// Skapar ett GUI-objekt som refererar båda pulsgeneratorerna,
// för att kunna visa och styra deras frekvenser på LCD.
GUI gui = initGUI(&pulseGen1, &pulseGen2);

// Skapar ett Button-objekt som kopplas till GUI för att byta generator/frekvens.
Button button = initButton(&gui);

// Skapar ett InterruptHandler-objekt som kopplas till button för att kunna calla button funktionerna.
Interrupthandler interrupt = initInterruptHandler(&button);

// startProgram() körs vid uppstart. Den startar genereringen av pulser
// och anropar updateDisplay vid start.
int startProgram(GUI *self) {
	// Starta båda pulsgeneratorerna direkt (ASYNC så att vi inte blockerar).
	ASYNC(&pulseGen1, setPulse, 0);
	ASYNC(&pulseGen2, setPulse, 0);

	// Uppdatera displayen omedelbart så vi ser initialfrekvenser (0).
	ASYNC(self, updateDisplay, 0);

	return 0;
}

int main(void) {
	// Initiera timer/klocka via avr_init().
	avr_init();
	
	// Initiera LCD innan vi börjar skriva ut.
	lcd_init();
	
	// Initiera knappar (pullups + pin change interrupt).
	btn_init();

	// Installera knappobjektet som interrupthandler för PCINT0 och PCINT1.

	INSTALL(&interrupt, horizontal, IRQ_PCINT0);
	INSTALL(&interrupt, vertandcent, IRQ_PCINT1);

	// TINYTIMBER startar kernel. Vi anropar startProgram på gui som första metod.
	return TINYTIMBER(&gui, startProgram, 0);
}
