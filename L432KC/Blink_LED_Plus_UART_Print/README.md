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
The first part of a section definition is the name. 
Here the first section of program in Flash memory should be the vector table.\
We label this .vectors. Linkers usually default to placing this at the start of Flash so you may"\
see other linker script which do not do this. It is good practice to be explicit though.\

Within our section we  have 
```
 KEEP(*(.isr_vector))
```
This keep symbol ensures that specified sections or symbols are not optimized out by the linker.\
In this case we want to ensure that the .isr\_vector section will not be optimized out.

```
> FLASH
```
This Section tells us where the section should be placed. In this example we place our vector table in flash memory.

```

.data :
		{
			. = ALIGN(8);    /* Align start of data segment to 8 byte boundary */
			_sdata =  .;     /* Global Variable located at start of data segment */
			
			*(.data)         /* Coallesce all data input data segment */
			*(.data.*)       /* Coallesce all .data sub-setions (e.g, .data.foo, .data.bar) */
		
			. = ALIGN (8);  
			_edata = .;      /* Global symbol located at end of segment */
		} > SRAM AT > FLASH   /* Load into Flash but copy the data into SRAM */
```
Above is we have a snippet describing the .data section. This section contains initialized global and static variables.\
The ALIGN(8) tell us to align the start data section on an 8 byte boundary. Following that we have \_sdata which is a global variable which points to the start of the data segement. We also have \_edata which points to the end. These will be useful in the startup script.\

```
 *(.data)
```
Each .c program will have a data section. If we are linking multipled files the \*() notation tells the the linker to coallesce all the data segments of each program into this seciont.  

```
> SRAM AT > FLASH
```

Lastly SRAM AT> FLASH tells the linker that we are we want to store the data in FLASH but load it into SRAM on boot. 

Startup.c

Next we have a simple implentation of a startup script. (Not to be confused with a bootloader)
In my startup script I define the Reset_Handler() IRQ, the interrupt vector table, zero out the .bss section and copy the .data sections from flash to SRAM. 


```
extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sidata;
```

The above are variable we defined in our linker script. These variables are  locationed in Flash memory in the order they were defined. By getting the address of these variables we can get the location of the various sections in flash. For example, in our linker script we define \_sdata symbol at the start of the data section in our linker script. In the linker script these are symbols but when we access using the extern keyword in startup.c we tread it as a variable. This means the  address of the variable tells us where the start of the data section is in flash. These will be useful for opertations we see later.
```
uint32_t vector_tb1[] __attribute__((section(".isr_vector"))) = {
	(uint32_t) &_estack,
	(uint32_t) &Reset_Handler,
	(uint32_t) &Default_Handler,
    ...
    (uint32_t) &Tim2_Handler
```

Here we define our interrupt vector table. The first entry contains the initial address of the stack pointer. This is because the first entry of the vector table is at the start of flash. On boot this value will be stored in MSP register which holds the address of the top of the stack.\
We also define add the locations of the Reset\_Handler and Tim2\_Handler. 

```
	uint32_t data_size = ((uint32_t)&_edata - (uint32_t)&_sdata);
	uint8_t * src = (uint8_t *)&_sidata; /*8 bit pointer for byte by byte copy */
	uint8_t * dst = (uint8_t *)&_sdata;  /*8 bit pointer for byte by byte copy */
	//copy data from flash to ram
	for(uint32_t i = 0; i < data_size; i++){
		dst[i] = src[i];
	}	
	
	uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	uint8_t * bss_ptr = (uint8_t *)&_sbss;
	//zero out bss
	for(uint32_t i = 0; i < bss_size; i++){
		bss_ptr[i] = 0;
	}
```
In this section of code we use the symbols defined in our linker scrip to copy the .data section to flash and zero out the .bss section one byte at a time. This could also be performed with larger chunks. 

```
    // enable interupts 
	asm volatile("cpsie i");	

	//call main 	
	main();
```
This last secion enables global interrupts and calls our main function.

