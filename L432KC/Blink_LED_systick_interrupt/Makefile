final : blink_led_systick_int.elf

main.o : main.c
	arm-none-eabi-gcc -c -O0 -g3 -Wall -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o main.o

startup.o : startup.c 
	arm-none-eabi-gcc -c -O0 -g3 -Wall -mcpu=cortex-m4 -mthumb -std=gnu11 startup.c -o startup.o

blink_led_systick_int.elf : main.o startup.o 
	arm-none-eabi-gcc -nostdlib -T linker.ld *.o -g3 -o blink_led_systick_int.elf -Wl,-Map=blink_led_systick_int.map

load:
	openocd -f /opt/homebrew/share/openocd/scripts/board/st_nucleo_l4.cfg

clean:
	rm -f *.o *.elf *.map
