#Main application file name
MAIN_APP = blink_sonar
# Compiler and other Section
CC = avr-gcc
OBJCOPY = avr-objcopy.exe
AVRDUDE = avrdude
PROCESSOR = atmega328p
UP_PROCESSOR = ATMEGA328P
PORT = COM7

#Options for avr-gcc
CFLAGS = -Os -DF_CPU=16000000L -mmcu=$(PROCESSOR) -c -o

#Options for HEX file generation
HFLAGS = -O ihex -R .eeprom

#Options for avrdude
DUDEFLAGS = -F -V -c arduino -p $(UP_PROCESSOR) -P $(PORT) -b 115200 -U flash:w:$(MAIN_APP).hex

# commands Section
Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)

Build : $(MAIN_APP).bin
	$(OBJCOPY) $(HFLAGS) $(MAIN_APP).bin $(MAIN_APP).hex

$(MAIN_APP).bin: $(MAIN_APP).o
	$(CC) -o $(MAIN_APP).bin $(MAIN_APP).o

$(MAIN_APP).o:$(MAIN_APP).c
	$(CC) $(CFLAGS) $(MAIN_APP).o $(MAIN_APP).c

clean:
	rm $(MAIN_APP).hex
	rm $(MAIN_APP).o
	rm $(MAIN_APP).bin

re : clean Burn