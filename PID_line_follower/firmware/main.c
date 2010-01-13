/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <pololu/3pi.h>

#define REFRESH 50
#define MAX_SPD 255

const char welcome_one[] PROGMEM = "MPL 3pi";
const char welcome_two[] PROGMEM = "Line";
const char welcome_three[] PROGMEM = "Follower";

const char enter[] PROGMEM = {
    0b01111,
    0b00001,
    0b00001,
    0b00101,
    0b01001,
    0b11111,
    0b01000,
    0b00100
};

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

unsigned int sensors[5];

void load_custom_chars() {
    lcd_load_custom_character(levels+0, 0);
    lcd_load_custom_character(levels+1, 1);
    lcd_load_custom_character(levels+2, 2);
    lcd_load_custom_character(levels+3, 3);
    lcd_load_custom_character(levels+4, 4);
    lcd_load_custom_character(levels+5, 5);
    lcd_load_custom_character(levels+6, 6);
    lcd_load_custom_character(enter, 7);
    clear();
}

void print_readings(const unsigned int *readings) {
    unsigned char i;
    for (i=0; i<5; i++) {
        const char display_characters[10] = {' ', 0, 0, 1, 2, 3, 4, 5, 6, 255};
        char c = display_characters[readings[i]/101];
        print_character(c);
    }
}

void initialize() {
    unsigned int counter;
    
    /*
     init the 3pi
     */
    pololu_3pi_init(2000);
    
    /*
     load our custom characters for the bar graphs
     */
    load_custom_chars();
    
    /*
     Run a scrolling message across the lcd, then clear
     */
    print_from_program_space(welcome_one);
    lcd_goto_xy(0, 1);
    print_from_program_space(welcome_two);
    delay_ms(2000);
    clear();
    lcd_goto_xy(0, 0);
    print_from_program_space(welcome_two);
    lcd_goto_xy(0, 1);
    print_from_program_space(welcome_three);
    delay_ms(2000);
    clear();
    
    /*
     Show battery levels whilst waiting for the signal
     to calibrate motors.
     */
    while (!button_is_pressed(BUTTON_B)) {
        int battery = read_battery_millivolts();
        char e = 7;
        clear();
        print_long(battery);
        print(" mV");
        lcd_goto_xy(0, 1);
        print("Press B");
        print_character(e);
        delay_ms(500);
    }
    wait_for_button_release(BUTTON_B);
    delay_ms(1000);
    
    /*
     Turn the motors side to side while calibrating
     the line sensors.  This will show us the disipation
     times.
     */
    for (counter = 0; counter < 80; counter++) {
        if (counter < 20 || counter >= 60) {
            set_motors(40, -40);
        } else {
            set_motors(-40, 40);
        }
        calibrate_line_sensors(IR_EMITTERS_ON);
        delay_ms(20);
    }
    set_motors(0, 0);
    
    /*
     While waiting for button A to be pressed display the remaining
     battery voltage in mV and use a bar graph to indicate the levels
     of light reading coming from the sensors
     */
    while (!button_is_pressed(BUTTON_A)) {
        char e = 7;
        clear();
        
        /*
         Uncomment this if you want to display battery
         information rather than position
        */
        int battery = read_battery_millivolts();
        print_long(battery);
        print(" mV");
        
        /*
         Uncomment this if you want to display position
         information rather than battery
         */
        //int pos = read_line(sensors, IR_EMITTERS_ON);
        //print_long(pos);
        
        lcd_goto_xy(0, 1);
        print_readings(sensors);
        lcd_goto_xy(6, 1);
        print("A");
        print_character(e);
        delay_ms(100);
    }
    wait_for_button_release(BUTTON_A);
    clear();
    
    /*
     The button has been pressed and released and we are
     now ready to move onto actually following a line.
     */
    print("WEWT!!!");
    delay_ms(2000);
}

int main(void)
{
    int counter = 0;
    int integral = 0;
    int last_prop = 0;
    
    initialize();
    
    while (1) {
        unsigned int pos = read_line(sensors, IR_EMITTERS_ON);
        if (counter < REFRESH) {
            counter++;
        } else if (counter == REFRESH) {
            counter = 0;
            int battery = read_battery_millivolts();
            clear();
            print_long(battery);
            print(" mV");
            lcd_goto_xy(0, 1);
            print_readings(sensors);
        }
        
        int prop = ((int)pos) - 2000;
        int deriv = prop - last_prop;
        integral += prop;
        last_prop = prop;
        
        int power_diff = prop/10 + integral/6000 + deriv*9/5;
        
        if(power_diff > MAX_SPD)
            power_diff = MAX_SPD;
        if(power_diff < -MAX_SPD)
            power_diff = -MAX_SPD;
        
        if(power_diff < 0)
            set_motors(MAX_SPD + power_diff, MAX_SPD);
        else
            set_motors(MAX_SPD, MAX_SPD - power_diff);
    }
    
    /*
     Never reached
     */
    return 0;
}
