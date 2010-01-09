# Name: Makefile
# Author: Daniel Salinas
# Copyright: Daniel Salinas (2009)
# License: GPL v3

##################
# Device Section #
##################
DEVICE = atmega168
AVRDUDE_DEVICE = m168
CLOCK = 20000000

###################
# Library Section #
###################
AVRLIB = /opt/libs/avrlib
VUSBLIB = /opt/libs/vusb-20090822

# Use the LDFLAGS with "pololu" if doing
# 3pi development or if you just want to
# use the 3pi libraries.
#LDFLAGS = -Wl,-gc-sections -Wl,-relax
LDFLAGS = -Wl,-gc-sections -lpololu_$(DEVICE) -Wl,-relax


######################
# Programmer Section #
######################
PROGRAMMER = avrisp2
PORT = usb
AVRDUDE = avrdude -c $(PROGRAMMER) -P $(PORT) -p $(AVRDUDE_DEVICE)

####################
# Compiler Section #
####################
CFLAGS = -g -Wall -mcall-prologues -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -Os -Iusbdrv -I. -I$(shell cd ${AVRLIB}; pwd)
CPP = avr-g++
CC = avr-gcc
OBJ2HEX = avr-objcopy
TARGET = main
OBJECTS = $(TARGET).o

# symbolic targets:
all:	$(TARGET).hex

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(CC) $(CFLAGS) -S $< -o $@

#main.elf: $(OBJECTS)
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).elf $(OBJECTS)

#main.hex: main.elf
#	rm -f main.hex
#	$(OBJ2HEX) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

disasm: main.elf
	$(OBJ2HEX) -d main.elf

cpp:
	$(CPP) $(CFLAGS) -E main.c

clean:
	rm -f *.o *.hex *.obj *.elf $(OBJECTS)

#%.hex: %.obj
#	rm -f $(TARGET).hex
#	$(OBJ2HEX) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

%.hex: %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

%.obj: %.o
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(TARGET).hex

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash

# Since we don't want to ship the driver multiple times, we copy it into this project:
usbdrv:
	cp -r $(VUSBLIB)/usbdrv .