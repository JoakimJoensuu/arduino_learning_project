build_and_flash:
	mkdir -p build
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o build/blink_led.o src/blink_led.c
	avr-gcc -mmcu=atmega328p build/blink_led.o -o build/blink_led
	avr-objcopy -O ihex -R .eeprom build/blink_led build/blink_led.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/blink_led.hex

build_and_run:
	gcc -c src/blink_led.c -Dx86 build/blink_led
	./build/blink_led