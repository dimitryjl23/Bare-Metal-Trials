#include <stdint.h> 

#ifndef GPIO_H
#define GPIO_H

//lets use structs
//
typedef struct{
	volatile uint32_t MODER;    /*offset: 0x0 */
	volatile uint32_t OTYPER;   /*offset: 0x4 */
	volatile uint32_t OSPEEDR;  /*offset: 0x8 */
	volatile uint32_t PUPDR;    /*offset: 0xC */
	volatile uint32_t IDR;		/*offset: 0x10 */
	volatile uint32_t ODR;		/*offset: 0x14 */
	volatile uint32_t BSRR;		/*offset: 0x18 */
	volatile uint32_t LCKR;     
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;

} GPIO_TypeDef;





#endif
