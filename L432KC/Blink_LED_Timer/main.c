#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "gpio.h"
#include "rcc.h"
#include "timer.h"
#include "nvic.h"


#define GPIO_B  ((GPIO_TypeDef *) GPIOB_BASE)
#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define TIM2 ((TIMER_TypeDef *) TIM2_BASE)
#define TIM2_IRQn 28


void init_gpio(){
	RCC->AHB2_ENR |= (1U << 1);          // Enable GPIO A Clock
	GPIO_B->OSPEEDR &= ~(3U << (3 *2));  // Clear the bit
	GPIO_B->OSPEEDR |= (3 << (3 * 2));   // Set the output speed to high
	GPIO_B->MODER &= ~(3U << (3 * 2));   // Clear the bit 
	GPIO_B->MODER |= (1U << (3 * 2));    // Set mode to output
}


void enable_interrupt(uint32_t IRQ_num){
	NVIC_ISER |= (1U << IRQ_num);
}

void disable_interrupt(uint32_t IRQ_num){
	NVIC_ICER |= (1U << IRQ_num); 
}

#if 0
void set_systick_interrupt_priority(int priority){
	uint32_t reg_index = SysTick_IRQn / 4;     // Each IPR reg holds 4 interrupts
	uint32_t shift = (SysTick_IRQn % 4) * 8;   // Each interrupt register hold 8 bits
	//*((volatile uint8_t*)(&NVIC_IPR[reg_idx] + 1)) = (priority << shift);
}

#endif 

void init_tim2(){
	
	// Enable Clock for TIM2
	RCC->APB1_ENR |= 0x00000001;
	
    /*
	 * UEV: Update Event Frequency 
	 *
	 * UEV = (Bus_Clock) / ((Prescaler + 1)(Period + 1)) 
	 * 
	 * Goal UEV of 1 Hz
	 * Bus_Clock = APB1_Bus Freq = 16Mhz
	 * 
	 * To achieve 1Hz we Prescaler = 15999, Period = 999
	 *
	 * 16,000,000 / ((15999 + 1)(999+1)) = 1 Hz
	 */

	// Set Auto Reload Register 
	TIM2->ARR = 999;

	// Set Prescaler 
	TIM2->PSC = 15999;
	
	// Set TIM2 COUNT
	TIM2->CNT = 0;

	// Enable TIM2 Interrupts
	TIM2->DIER |= 0x00000001; 
	
	// Enable TIM2
	TIM2->CR1 |= 0x00000001; 	
}

void Tim2_Handler(void){
	
	// Toggle the LED
	GPIO_B->ODR ^= (1U << 3);
		
	// Clear Update interrupt pending flag
	if (TIM2->SR & 0x00000001) {
		TIM2->SR &= ~0x00000001;
	}
}

int main(){

	// intialize GPIO B
	init_gpio();
	
	// initialize tim2
	init_tim2();
	
	// Toggle GPIO B 3
	GPIO_B->ODR |= (1U << 3);
	
	// Enable Tim2 in NVIC
	enable_interrupt(TIM2_IRQn);
	
	while(1) {
		// Wait for an interrupt
	}

	// Disable Tim2
	TIM2->CR1 &= ~(1U << 0);
	
	// Disable Tim2 NVIC interrupt
	disable_interrupt(TIM2_IRQn);

}	
