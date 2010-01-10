/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <pololu/3pi.h>

const char welcome_one[] PROGMEM = "Welcome to the overly inspirational program I wrote to display battery information and light sensor information";

unsigned int sensor_values[5];

const char levels[] PROGMEM = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

void load_custom_chars() {
    load_custom_character(levels+0, 0);
    load_custom_character(levels+1, 1);
    load_custom_character(levels+2, 2);
    load_custom_character(levels+3, 3);
    load_custom_character(levels+4, 4);
    load_custom_character(levels+5, 5);
    load_custom_character(levels+6, 6);
    clear();
}

void print_readings(const unsigned int *readings) {
    unsigned char i;
    for (i=0; i<5; i++) {
        const char disp_chars[10] = {' ', 0, 0, 1, 2, 3, 4, 5, 6, 255};
        
    }
}

int main(void)
{
    pololu_3pi_init(2000);
    read_line_sensors(sensor_values);
}
