#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "gpio.h"
#include "rcc.h"
#include "timer.h"
#include "nvic.h"
#include "usart.h"

#define GPIO_B  ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIO_A  ((GPIO_TypeDef *) GPIOA_BASE)
#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define USART2 ((USART_TypeDef*) USART2_BASE)
#define TIM2 ((TIMER_TypeDef *) TIM2_BASE)
#define TIM2_IRQn 28


void init_gpio(){
	RCC->AHB2_ENR |= (1U << 1);          // Enable GPIO A Clock
	GPIO_B->OSPEEDR &= ~(3U << (3 *2));  // Clear the bit
	GPIO_B->OSPEEDR |= (3 << (3 * 2));   // Set the output speed to high
	GPIO_B->MODER &= ~(3U << (3 * 2));   // Clear the bit 
	GPIO_B->MODER |= (1U << (3 * 2));    // Set mode to output
	

}

//PA2 set to AF7 for USART 2 TX
void init_usart(){

	// Enable RCC GPIO A
	RCC->AHB2_ENR |= (1U << 0);

	// Clear + Set PA2 to Alternate Function Mode
	GPIO_A->MODER &= ~(3U << (2 * 2));
	GPIO_A->MODER |= (2U << (2 * 2));
     
	// Clear + Set PA2 Alternate Function to AF7
	GPIO_A->AFRL &= ~(15U << (2 * 4));
	GPIO_A->AFRL |=  (7U << (2 * 4));

	// Enable USART2 RCC 
	RCC->APB1_ENR |= (1U << 17);
			
	// Configure Baud Rate... for some reason we only see output when terminal baud is 14400
	// Also I am pretty sure the default clock is 4Mhz, need to investigate.... but it works!
	//USART2->BRR = (4000000 + (9600 / 2U)) / 9600;
	USART2->BRR = (16000000/9600);
	
	// Enable Transmitter and UART;
	USART2->CR1 |= (0x00000008 | 0x00000001);

}

void put_char_usart(char byte){
	
	// Wait until no pending transmissions
	while(!(USART2->ISR & (1U << 7)));	

	// Lod bye in to transmission data register
	USART2->TDR = byte;
}

void enable_interrupt(uint32_t IRQ_num){

	NVIC_ISER |= (1U << IRQ_num);
}

void disable_interrupt(uint32_t IRQ_num){
	
	NVIC_ICER |= (1U << IRQ_num); 
}


void init_tim2(){
		
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

	// Enable Clock for TIM2
	RCC->APB1_ENR |= 0x00000001;
	
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

void delay(uint32_t val){
	uint32_t i = 0;
	while (i < val){
		asm("nop");
		i++;
	}
}

int main(){

	// intialize GPIO B
	init_gpio();
    	
	// initialize tim2
	init_tim2();
	
	// initialize uart
	init_usart();

	// Toggle GPIO B 3
	GPIO_B->ODR |= (1U << 3);
	
	// Enable Tim2 in NVIC
	enable_interrupt(TIM2_IRQn);
	
	while(1) {
	    char * str = "Hello World\n";
		while(*str){
			put_char_usart(*str++);	
		}
	}
	
	// Disable Tim2
	TIM2->CR1 &= ~(1U << 0);
	
	// Disable Tim2 NVIC interrupt
	disable_interrupt(TIM2_IRQn);

}	
