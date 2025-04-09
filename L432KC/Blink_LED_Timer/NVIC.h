#ifndef NVIC_H
#define NVIC_H


#define NVIC_ISER (*(volatile uint32_t *)(0xE000E100))   // NVIC interrupt set enable reg
#define NVIC_ICER (*(volatile uint32_t *)(0xE000E180))   // NVIC interrupt clear enable reg
#define NVIC_IPR (*(volatile uint32_t *)(0xE000E400))    // NVIC interrupt priority reg

#endif
