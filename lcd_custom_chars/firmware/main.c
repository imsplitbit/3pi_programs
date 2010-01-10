/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

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

const char sad[] PROGMEM = {
    0b00000,
    0b01010,
    0b01010,
    0b01010,
    0b00000,
    0b01110,
    0b10001,
    0b00000
};

const char indifferent[] PROGMEM = {
    0b00000,
    0b01010,
    0b01010,
    0b01010,
    0b00000,
    0b00000,
    0b01110,
    0b00000
};

const char surprised[] PROGMEM = {
    0b00000,
    0b01010,
    0b01010,
    0b00000,
    0b01110,
    0b10001,
    0b10001,
    0b01110
};

const char mocking[] PROGMEM = {
    0b00000,
    0b01010,
    0b01010,
    0b01010,
    0b00000,
    0b11111,
    0b00101,
    0b00010
};

char prev_mood = 5;

int main(void)
{
    lcd_load_custom_character(happy, 0);
    lcd_load_custom_character(sad, 1);
    lcd_load_custom_character(indifferent, 2);
    lcd_load_custom_character(surprised, 3);
    lcd_load_custom_character(mocking, 4);
    clear();
    print("MOOD: ?");

    wait_for_button_press(ALL_BUTTONS);
    long seed = 0;
    while (button_is_pressed(ALL_BUTTONS)) {
        seed++;
    }
    srandom(seed);

    while (1) {
        lcd_goto_xy(6,0);
        char mood;
        do {
            mood = random() % 5;
        } while (mood == prev_mood);
        prev_mood = mood;
        print_character(mood);
        wait_for_button(ALL_BUTTONS);
    }
    return 0;   /* never reached */
}
