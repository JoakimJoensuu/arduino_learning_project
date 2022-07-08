build_and_flash:
	mkdir -p build
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/print.o src/print.c
	avr-gcc -mmcu=atmega328p build/print.o -o build/print
	avr-objcopy -O ihex -R .eeprom build/print build/print.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/print.hex
	stty 9600 -F /dev/ttyACM0 raw -echo
	cat /dev/ttyACM0

build_and_run:
	gcc -c src/print.c -Dx86 build/print
	./build/print