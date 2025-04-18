ENTRY(Reset_Handler)  /* Specifies entry point of the program */

MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K /* Origin + Length of Flash Memory Region */
	SRAM  (rw) : ORIGIN = 0x20000000, LENGTH = 64K  /* Origin + Lengh of SRAM Region */
}


_estack = ORIGIN(SRAM) + LENGTH(SRAM);    /* Stack points to end of SRAM */
_eflash = ORIGIN(FLASH) + LENGTH(FLASH);  /* points to end of flash */

__max_heap_size = 0x200;
__max__stack_size = 0x400;

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
			
		.rodata :           /* Read only data. Could also be placed in Text */
		{
			. = ALIGN(8);
			*(.rodata)

			. = ALIGN(8);
		} > FLASH
        
		.data :
		{
			. = ALIGN(8);    /* Align start of data segment to 8 byte boundary */
			_sdata =  .;     /* Global Variable located at start of data segment */
			
			*(.data)         /* Coallesce all data input data segment */
			*(.data.*)       /* Coallesce all .data sub-setions (e.g, .data.foo, .data.bar) */
		
			. = ALIGN (8);  
			_edata = .;      /* Global symbol located at end of segment */
		} > SRAM AT > FLASH   /* Load into Flash but copy the data into SRAM */
       
	   	_sidata = LOADADDR(.data); /* We need the Flash address of data to copy to RAM */

		.bss :              /* .bss for uninit global + static vars */
		{ 
			. = ALIGN(8);
			_sbss = .;
			*(.bss)	
			
			. = ALIGN(8);
			_ebss = .;
		} > SRAM          /* Stored in SRAM */
	}
