#include "base.h"

#ifndef RCC_H
#define RCC_H

typedef struct
{
	volatile uint32_t DUMMY[19];  /* A Paddng of 0x4B 19*4 = 76 */
	volatile uint32_t AHB2_ENR;  /* Offset 0x4C */ 

} RCC_TypeDef;

#endif 
