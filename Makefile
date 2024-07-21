SERIAL_PORT=/dev/ttyACM0
run:
	avr-gcc -mmcu=atmega2560 -DF_CPU=16000000UL -Os -c blink_mega.c -o blink_mega.o
	avr-gcc -mmcu=atmega2560 -DF_CPU=16000000UL -Os blink_mega.o -o blink_mega.elf
	avr-objcopy -O ihex -R .eeprom blink_mega.elf blink_mega.hex
	avrdude -patmega2560 -cwiring -P/dev/ttyACM0 -b115200 -D -Uflash:w:blink_mega.hex:i

perms:
	sudo usermod -a -G uucp $$USER
	sudo chmod a+rw $(SERIAL_PORT)

#Open the datasheet with pins and schematic of the Arduino Mega 2560 (ATMega2560)
pin_datasheet:
	firefox https://download.lulzbot.com/AO-100/hardware/electronics/ArduinoMEGA_2560/PinMapping2560.html

#Use 'Ctrl+A' then 'K' to stop
screen:
	screen $(SERIAL_PORT)
