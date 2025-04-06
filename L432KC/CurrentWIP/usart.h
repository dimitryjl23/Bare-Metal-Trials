#ifndef USART_H
#define USART_H

#include <stdint.h>

typedef struct{
	uint32_t CR1;   // 0x0
	uint32_t CR2;   // 0x04
	uint32_t CR3;   // 0x08
	uint32_t BRR;   // 0x0C
	uint32_t PAD1;	// 0x10
	uint32_t RTOR;  // 0x14
	uint32_t RQR;   // 0x18
	uint32_t ISR;   // 0x1C
	uint32_t ICR;   // 0x20
	uint32_t RDR;   // 0x24
	uint32_t TDR;   // 0x28
} USART_Typedef;

#endif
