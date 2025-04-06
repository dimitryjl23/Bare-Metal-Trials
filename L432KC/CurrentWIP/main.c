#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"
#include <unistd.h>

#define GPIO_B  ((GPIO_TypeDef *) GPIOB_BASE)
#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define USART2   ((USART_TypeDef *) USART2_BASE)
void init_gpio(){
	RCC->AHB2_ENR |= (1U << 1);          // Enable GPIO A Clock
	GPIO_B->OSPEEDR &= ~(3U << (3 *2));  // Clear the bit
	GPIO_B->OSPEEDR |= (3 << (3 * 2));   // Set the output speed to high
	GPIO_B->MODER &= ~(3U << (3 * 2));   // Clear the bit 
	GPIO_B->MODER |= (1U << (3 * 2));    // Set mode to output
}

void init_usart(){

	//Configure GPIO Pin for USART	
	RCC->APB1_ENR |= (1U << 17); // Enabled USART2 Clock
	USART2->CR1 |= (1U << 3);     // Enable USART Transmite
	USART2->CR1 |= (1U << 2);	 // Enable USART Reciever
	USART2->CR1 |= (1U << 0);    // Enable USART
    USART2->CR1  |= (1U << 10);  // Enable Parity Control	    								   	
}

void blink_led(){
	GPIO_B->ODR ^= (1U << 3);  	
}

void init_uart(){
	// Do Nothing
}

void delay(int val){
	int i = 0;
	while(i < val){
		asm("nop");
		i++;
	}
}
int main(){
	
	init_gpio();
    GPIO_B->ODR |= (1U << 3);
	while(1) {
		blink_led();
		delay(1000000);
	}
}
