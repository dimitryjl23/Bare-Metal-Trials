final : morse_code_project.elf

main.o : main.c
	arm-none-eabi-gcc -c -O0 -g3 -Wall -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o main.o

startup.o : startup.c 
	arm-none-eabi-gcc -c -O0 -g3 -Wall -mcpu=cortex-m4 -mthumb -std=gnu11 startup.c -o startup.o

morse_code_project.elf : main.o startup.o 
	arm-none-eabi-gcc -nostdlib -T linker.ld *.o -g3 -o morse_code_project.elf -Wl,-Map=morse_code_project.map

load:
	openocd -f /opt/homebrew/share/openocd/scripts/board/st_nucleo_l4.cfg

clean:
	rm -f *.o *.elf *.map
