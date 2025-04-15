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
This section defines lets the compiler know where specific memory regions are located.\
In this case our micrcontroller FLASH region is located at 0x80000000, has a size of 256KB, and has read+execute permissions.\
The SRAM resgion is located at 0x20000000, has a size of 64KB, and has read+write permissions.

Using the reference manual we 
