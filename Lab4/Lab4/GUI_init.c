/*
 * GUI_init.c
 *
 * Created: 21/02/2025 08:56:23
 *  Author: johan_csf2sgl
 */ 


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
	// Drive Time = 300 µs (LCDDC2 & LCDDC1 & LCDDC0 = 0)
	// Contrast Control Vol	tage = 3.35 V (LCDCC3 & LCDCC2 & LCDCC1 & LCDCC0 = 1)
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
}