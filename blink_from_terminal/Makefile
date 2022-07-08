build_and_flash:
	mkdir -p build
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/blink_from_terminal.o src/blink_from_terminal.c
	avr-gcc -mmcu=atmega328p build/blink_from_terminal.o -o build/blink_from_terminal
	avr-objcopy -O ihex -R .eeprom build/blink_from_terminal build/blink_from_terminal.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/blink_from_terminal.hex
	stty 9600 -F /dev/ttyACM0 raw -echo
	bash -c "cat /dev/ttyACM0" &

build_and_run:
	gcc -c src/blink_from_terminal.c -Dx86 build/blink_from_terminal
	./build/blink_from_terminal