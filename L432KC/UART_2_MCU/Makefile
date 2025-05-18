CFLAGS ?= -c -O0 -g3 -Wall -mcpu=cortex-m4 -mthumb -std=gnu11 \
          -I. -Iinclude -Icmsis_core/CMSIS/Core/Include -Icmsis_l4/Include 
LDFLAGS ?=  -nostdlib -T linker.ld *.o -g3 -o uart_write.elf -Wl,-Map=$@.map 
SOURCES = main.c startup.c
STARTUP_SOURCE = cmsis_l4/Source/Templates/gcc/startup_stm32l432xx.s
SYSTEM_SOURCE = cmsis_l4/Source/Templates/system_stm32l4xx.c

final : uart_write.elf

gpio.o : gpio.c
	arm-none-eabi-gcc $(CFLAGS) gpio.c -o $@

main.o : main.c
	arm-none-eabi-gcc $(CFLAGS) main.c -o $@

startup.o : startup.c 
	arm-none-eabi-gcc $(CFLAGS) startup.c -o $@

system.o: $(SYSTEM_SOURCE) 
	arm-none-eabi-gcc $(CFLAG) $(STARTUP_SOURCE) -o $@

# startup.o : $(STARTUP_SOURCE)
#	arm-none-eabi-gcc $(CFLAGS) $(STARTUP_SOURCE) -o $@

uart_write.elf : main.o gpio.o startup.o  
	arm-none-eabi-gcc $(LDFLAGS)  

load:
	openocd -f /opt/homebrew/share/openocd/scripts/board/st_nucleo_l4.cfg

cmsis_core:
	git clone --depth 1 -b 5.9.0 https://github.com/ARM-software/CMSIS_5 $@

cmsis_l4:
	git clone --depth 1 -b v1.7.4 https://github.com/STMicroelectronics/cmsis-device-l4 $@

libs: cmsis_core cmsis_l4

flash: 
	openocd -s /opt/homebrew/share/openocd/scripts/interface/stlink.cfg -f /opt/homebrew/share/openocd/scripts/board/st_nucleo_l4.cfg -c "program uart_write.elf verify reset exit"

clean:
	rm -rf *.o *.elf *.map 
