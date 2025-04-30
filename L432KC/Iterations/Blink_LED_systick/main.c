#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "gpio.h"
#include "rcc.h"
#include "systick.h"

#define GPIO_B  ((GPIO_TypeDef *) GPIOB_BASE)
#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define SYSTICK ((SYSTICK_TypeDef *) SYSTICK_BASE)

void init_gpio(){
	RCC->AHB2_ENR |= (1U << 1);          // Enable GPIO A Clock
	GPIO_B->OSPEEDR &= ~(3U << (3 *2));  // Clear the bit
	GPIO_B->OSPEEDR |= (3 << (3 * 2));   // Set the output speed to high
	GPIO_B->MODER &= ~(3U << (3 * 2));   // Clear the bit 
	GPIO_B->MODER |= (1U << (3 * 2));    // Set mode to output
}

void init_systick(){
	// SYSTICK->CSR |= (1U << 1); // Enable SysTick Interrupt						 
	SYSTICK->CSR |= (1U << 2);    // Set the Clk Src to Processor
}

void blink_led(){
	GPIO_B->ODR ^= (1U << 3);  	
}

void delay_systick(int ms){
	uint32_t ms_delay_val = 4000; // 4Mhz clock -> 4k cycles in 1 ms
    SYSTICK->RVR = ms_delay_val - 1;	
	SYSTICK->CVR = 0;             // Clear the systick current val reg. 
    SYSTICK->CSR |= (1U << 0);    // Enable Systick
    
	for(int i=0; i < ms; i++){
		while((SYSTICK->CSR & (1U << 16)) == 0) 
		{
			// spin. Once the above expression == 1, 1 ms has passed.
		}
	}

	SYSTICK->CSR &= ~(1U << 0);
}

int main(){
	
	init_gpio();
	GPIO_B->ODR |= (1U << 3);
	while(1) {
		blink_led();
		delay_systick(4000);
	}
}
