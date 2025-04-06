#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "gpio.h"
#include "rcc.h"
#include "uart.h"
#include <unistd.h>

#define GPIO_A  ((GPIO_TypeDef *) GPIOA_BASE)
#define RCC     ((RCC_TypeDef *) RCC_BASE)

void init_gpio(){
	RCC->AHB2_ENR |= (1U << 1);          // Enable GPIO A Clock
	GPIO_A->OSPEEDR &= ~(3U << (3 *2));  // Clear the bit
	GPIO_A->OSPEEDR |= (3 << (3 * 2));   // Set the output speed to high
	GPIO_A->MODER &= ~(3U << (3 * 2));   // Clear the bit 
	GPIO_A->MODER |= (1U << (3 * 2));    // Set mode to output
}

void blink_led(){
	GPIO_A->ODR ^= (1U << 3);  	
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
    GPIO_A->ODR |= (1U << 3);
	while(1) {
		blink_led();
		delay(1000000);
	}
}
