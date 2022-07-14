build_and_flash:
	mkdir -p build
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/motor_spinning.o src/motor_spinning.c
	avr-gcc -mmcu=atmega328p build/motor_spinning.o -o build/motor_spinning
	avr-objcopy -O ihex -R .eeprom build/motor_spinning build/motor_spinning.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/motor_spinning.hex
	stty 9600 -F /dev/ttyACM0 raw -echo

build_and_run:
	gcc -c src/motor_spinning.c -Dx86 build/motor_spinning
	./build/motor_spinning