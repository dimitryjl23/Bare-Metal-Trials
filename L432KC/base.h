#ifndef BASE_H
#define BASE_H

//IO Region Base Address
#define IO_BASE (0x40000000)

// APB1 Bus------------------------------------------
#define APB1_OFFSET (0x0)
#define APB1_BASE (IO_BASE + APB1_OFFSET)

// APB2 Bus------------------------------------------
#define APB2_OFFSET (0x00010000)
#define APB2_BASE (IO_BASE + APB2_OFFSET)

#define USART1_OFFSET (0x00001000)
#define USART1_BASE (APB2_BASE + USART1_OFFSET)

// AHB1 Bus------------------------------------------
#define AHB1_OFFSET (0x00020000)
#define AHB1_BASE (IO_BASE + AHB1_OFFSET)


#define GPIOA_OFFSET (0x0)
#define GPIOA_BASE (AHB1_BASE + GPIOA_OFFSET)

// AHB2 Bus-----------------------------------------
#define AHB2_OFFSET (0x20000000)
#define AHB2_BASE (IO_BASE + AHB2_OFFSET)

// RCC ----------------------------------------------
#define RCC_OFFSET (0x00023800)
#define RCC_BASE (IO_BASE + RCC_OFFSET)

#endif /* BASE_H */
