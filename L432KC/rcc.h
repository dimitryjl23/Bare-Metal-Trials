#include "base.h"

#ifndef RCC_H
#define RCC_H

typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1_ENR;

} RCC_TypeDef;

#endif 
