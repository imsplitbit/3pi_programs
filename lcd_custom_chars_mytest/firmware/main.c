/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <pololu/3pi.h>
#include <avr/pgmspace.h>

const char smile[] PROGMEM = {
    0b00100,
    0b01110,
    0b11111,
    0b00100,
    0b00100,
    0b11111,
    0b01110,
    0b00100
};

int this_row = 0;
int this_col = 0;

int main(void)
{
    lcd_load_custom_character(smile, 0);
    clear();
    while (1) {
        for (this_row = 0; this_row <= 1; this_row++) {
            <#statements#>
                }
        for (i = 0; i <= 7; i += 2) {
            char output = 0;
            lcd_goto_xy(i, 0);
            print_character(output);
            delay_ms(500);
        }
    }
    return 0;   /* never reached */
}
