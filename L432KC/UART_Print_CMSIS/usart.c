#include "base.h"
#include "usart.h"
#include "gpio.h"

#define USART_2 ((USART_TypeDef*)(USART2_BASE))
#define RCC     ((RCC_TypeDef *) RCC_BASE)

void init_usart(void){
	

	//Enable USART RCC 
	RCC->CR1 |= (1U << 17);

	// Enable USART2
	USART->CR1 |= 0x00000001;
	
	// Enable Transmitter;
	USART->CR1 |= 0x00000004;
	
	// Set the Word Length
	USART->CR1 &= 

	//Configure Baud Rate
	USART->BRR = 115000;
}

void put_char_usart(void){
	
	// Write value to the data regsiter
	
}

