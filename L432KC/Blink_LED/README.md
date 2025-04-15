Goal: We blink an LED until the end of time.\
This is the first iteration of the bare metal programming Trials. I will try my best to explain what I have in these mini projects.

Linker Script: linker.ld 

This script is responsible for various tasks.
I kept my linker script fairly simple and will walk through and describe each part. 

```
ENTRY(Reset_Handler)
```
Line one of our linker script specifies the entry point of our program. This means that after a flash and reset (or just reset if already flahsed) our microcontroller will jump to our Reset_Handler which is defined in our startup code (Startup.c)


```
MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K /* Origin + Length of Flash Memory Region */
	SRAM  (rw) : ORIGIN = 0x20000000, LENGTH = 64K  /* Origin + Lengh of SRAM Region */
}
```
This section defines lets the linker know where specific memory regions are located.\
The FLASH region is located at 0x80000000, has a size of 256KB, and has read+execute permissions.\
The SRAM resgion is located at 0x20000000, has a size of 64KB, and has read+write permissions.\
These can be found online or in the microcontroller specific reference manual.\

```
_estack = ORIGIN(SRAM) + LENGTH(SRAM);    /* Stack points to end of SRAM */
_eflash = ORIGIN(FLASH) + LENGTH(FLASH);  /* points to end of flash */
```
Here we define variables which point to the end of SRAM and the end of flash memory.\
These variables can be utilized in our startup.c file to configure our microcontroller correctly on reset.\
Later we will see how the estack variable is used in our vector table definition.\

```
__max_heap_size = 0x200;
__max_stack_size = 0x400;
```

These variables define the max size of the heap and the stack 
These variables define the max size of the heap and the stack. 
We set the max heap size to 512B and the max stack size to 1024B/1KB.\

```
SECTIONS
	{
		.vectors :  /* Setting vtable address to start of flash. Not Neccessary */ 
		{
			KEEP(*(.isr_vector))
		} > FLASH

		.text :              
		{
			. = ALIGN(8);
			*(.text)         /* Coallesce all input text segments */
			
			. = ALIGN(8);
		} > FLASH            /* Text stored in Flash Segment*/

    ... continued
```

The "Sections" section (pun) of the linker script defines where each section of program will be\
placed in memory.

```
.vectors :  /* Setting vtable address to start of flash. Not Neccessary */
        {
            KEEP(*(.isr_vector))
        } > FLASH 
```
The first part of a section definition is the name. Here the first section of program in Flash memory\
should be the vector table which we call denote by ".vectors"\

