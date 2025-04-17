#include "base.h"

#ifndef RCC_H
#define RCC_H

typedef struct
{
	volatile uint32_t DUMMY[19];  // 76 byte pad
	volatile uint32_t AHB2_ENR;   // Offset 0x4C
	volatile uint32_t DUMMY2[2];  // 8 byte pad
	volatile uint32_t APB1_ENR;   // Offset 0x58
} RCC_TypeDef;

#endif 
