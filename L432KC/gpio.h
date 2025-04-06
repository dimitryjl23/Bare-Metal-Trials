#include <stdint.h> 

#ifndef GPIO_H
#define GPIO_H

typedef struct{
	volatile uint32_t MODER;    // offset: 0x0
	volatile uint32_t OTYPER;   // offset: 0x4
	volatile uint32_t OSPEEDR;  // offset: 0x8 
	volatile uint32_t PUPDR;    // offset: 0xC 
	volatile uint32_t IDR;		// offset: 0x10 
	volatile uint32_t ODR;		// offset: 0x14 
	volatile uint32_t BSRR;		// offset: 0x18 
	volatile uint32_t LCKR;     // offset: 0x1C
	volatile uint32_t AFRL;     // ofsett: 0x20
	volatile uint32_t AFRH;     // offset: 0x24
	volatile uint32_t BRR;      // offset: 0x28

} GPIO_TypeDef;





#endif
