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

all: uart_two_way.hex

uart_two_way.hex: uart_two_way.elf
		$(OBJCOPY) -O ihex -R .eeprom $< $@

uart_two_way.elf: uart_two_way.o
		$(CC) $(CFLAGS) -o $@ $<

uart_two_way.o: uart_two_way.c
		$(CC) $(CFLAGS) -c -o $@ $<

upload: uart_two_way.hex
		$(AVRDUDE) -C $(AVRDUDECONFIG) $(PROGRAMMER) -U flash:w:uart_two_way.hex

clean:
		rm -f uart_two_way.o uart_two_way.elf uart_two_way.hex
