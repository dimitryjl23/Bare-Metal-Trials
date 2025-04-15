Goal: We blink an LED until the end of time.
This is the first iteration of the bare metal programming Trials.

Linker Script: linker.ld 

This script is responsible for various tasks. 

ENTRY(Reset_Handler)
Line one of our linker script specifies the entry point of our program. This means that after a flash and reset (or just reset if already flahsed) our microcontroller will jump to our Reset_Handler which is defined in our startup code. Startup.c


Using the reference manual we 
