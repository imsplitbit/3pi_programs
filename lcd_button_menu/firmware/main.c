/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <pololu/3pi.h>
#include <avr/pgmspace.h>

const char happy[] PROGMEM = {
	0b00000,
	0b01010,
	0b01010,
	0b01010,
	0b00000,
	0b10001,
	0b01110,
	0b00000
};

int main(void)
{
    lcd_load_custom_character(happy, 0);
	clear();
	char output = 0;
    
	while (1) {
        lcd_goto_xy(0,0);
        print("Push B");
        wait_for_button_press(BUTTON_B);
        clear();
		lcd_goto_xy(0,0);
		print_character(output);
        print(" YAY!");
		delay_ms(500);
        lcd_goto_xy(0,1);
        print("Push A");
        wait_for_button_press(BUTTON_A);
        clear();
	}
    return 0;   /* never reached */
}
