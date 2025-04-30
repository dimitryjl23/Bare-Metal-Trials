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

// I mistakenly though that systick was an NVIC interrupt :(
#if 0
void enable_systick_interrupt(){
	NVIC_ISER |= (1U << SysTick_IRQn); // systick at index 15
}

void disable_systick_interrupt(){
	NVIC_ICER |= (1U << SysTick_IRQn); 
}

void set_systick_interrupt_priority(int priority){
	uint32_t reg_index = SysTick_IRQn / 4;     // Each IPR reg holds 4 interrupts
	uint32_t shift = (SysTick_IRQn % 4) * 8;   // Each interrupt register hold 8 bits
	//*((volatile uint8_t*)(&NVIC_IPR[reg_idx] + 1)) = (priority << shift);
}

#endif 

void init_systick(){	
	SYSTICK->CSR |= (1U << 2);            // Set the Clk Src to Processor
	SYSTICK->CSR |= (1U << 1);            // Enable SysTick Interrupt						 
	uint32_t ms_delay_val = 16777215;     // 2^24-1 is max value we can hold in RVR
    SYSTICK->RVR = ms_delay_val - 1;	
	SYSTICK->CVR = 0;                     // Clear the systick current val reg. 
    SYSTICK->CSR |= (1U << 0);            // Enable Systick
 
}

void SysTick_Handler(void){
	GPIO_B->ODR ^= (1U << 3);
}

int main(){
	init_gpio();
	init_systick();
	GPIO_B->ODR |= (1U << 3);
	while(1) {
		// Wait for an interrupt
	}

	SYSTICK->CSR &= ~(1U << 0);  // Disable Systick
}	
