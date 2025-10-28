MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
CFLAGS = -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
AVRDUDECONFIG = "C:\ProgramData\arduino-ide-v2\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\etc\avrdude.conf"
PORT = COM4
BAUD = 115200
PROGRAMMER = -c arduino -p $(MCU) -P $(PORT) -b $(BAUD)

all: uart.hex

uart.hex: uart.elf
		$(OBJCOPY) -O ihex -R .eeprom $< $@

uart.elf: uart.o
		$(CC) $(CFLAGS) -o $@ $<

uart.o: uart.c
		$(CC) $(CFLAGS) -c -o $@ $<

upload: uart.hex
		$(AVRDUDE) -C $(AVRDUDECONFIG) $(PROGRAMMER) -U flash:w:uart.hex

clean:
		rm -f uart.o uart.elf uart.hex
