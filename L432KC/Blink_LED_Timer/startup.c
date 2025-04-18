#include <stdint.h>
#include <stddef.h>
extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sidata;

void Reset_Handler(void);   // Reset Handler
void Default_Handler(void); // Stub Handler so we dont need to write 16 prototypes
void main(void);
extern void Tim2_Handler(void);

uint32_t vector_tb1[] __attribute__((section(".isr_vector"))) = {
	(uint32_t) &_estack,
	(uint32_t) &Reset_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler, 
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,    // 15
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Default_Handler,
	(uint32_t) &Tim2_Handler        // 44
};

void Default_Handler(){
	// Do Nohing
}

void Reset_Handler(void){
    
	uint32_t data_size = ((uint32_t)&_edata - (uint32_t)&_sdata);
	uint8_t * src = (uint8_t *)&_sidata; /*8 bit pointer for byte by byte copy */
	uint8_t * dst = (uint8_t *)&_sdata;  /*8 bit pointer for byte by byte copy */
	//copy data from flash to ram
	for(uint32_t i = 0; i < data_size; i++){
		dst[i] = src[i];
	}	
	
	uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	uint8_t * bss_ptr = (uint8_t *)&_sbss;
	//zero out bss
	for(uint32_t i = 0; i < bss_size; i++){
		bss_ptr[i] = 0;
	}
    
    // enable interupts 
	asm volatile("cpsie i");	

	//call main 	
	main();
}	
