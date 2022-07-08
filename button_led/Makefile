build_and_flash:
	mkdir -p build
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/button_led.o src/button_led.c
	avr-gcc -mmcu=atmega328p build/button_led.o -o build/button_led
	avr-objcopy -O ihex -R .eeprom build/button_led build/button_led.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/button_led.hex

build_and_run:
	gcc -c src/button_led.c -Dx86 build/button_led
	./build/button_led