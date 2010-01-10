/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <pololu/3pi.h>

int main(void)
{
	while(1) {
		print("Hello");
		delay_ms(200);
		lcd_scroll(LCD_RIGHT, 3, 200);
		clear();
		lcd_goto_xy(3, 1);
		print("Hello");
		delay_ms(200);
		lcd_scroll(LCD_LEFT, 3, 200);
		clear();
	}
    return(0);
}
