#include "main.h"

int main(void)
{
	SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF3_ENABLE);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODIR_R.B.DIR, GPIO_PF3_ENABLE);
	
	/* Super Loop */
	while(1)
		{
			SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODATA_R.B.DATA, GPIO_PF3_ENABLE);
		}
}


//#define SYSCTL_RCGCGPIO_R (*(( volatile unsigned long *)0x400FE608 ) )
//#define GPIO_PORTF_DATA_R (*(( volatile unsigned long *)0x40025038 ) ) 
//#define GPIO_PORTF_DIR_R  (*(( volatile unsigned long *)0x40025400 ) ) 
//#define GPIO_PORTF_DEN_R  (*(( volatile unsigned long *)0x4002551C ) )


//int main ( void )
//{
//SYSCTL_RCGCGPIO_R |= 0x20; // Enable clock for PORTF
//GPIO_PORTF_DEN_R  = 0x0E;  // Enable PORTF Pin1, 2 and 3 as a digital pins
//GPIO_PORTF_DIR_R  = 0x0E;  // Configure ORTF Pin1, 2 and 3 digital output pins
//		
//	while (1) 
//		{  
//		GPIO_PORTF_DATA_R |= 0x08; // turn on red LED
//		}
//}
