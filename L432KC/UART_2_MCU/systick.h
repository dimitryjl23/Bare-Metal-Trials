#ifndef SYSTICK_H
#define SYSTICK_H

typedef struct{
	volatile uint32_t CSR;    // 0x10
	volatile uint32_t RVR;    // 0x14
	volatile uint32_t CVR;    // 0x18
	volatile uint32_t CALIB;  // 0x1C
} SYSTICK_TypeDef;

#endif
