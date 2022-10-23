#include "../Libraries/Bit_Manipulation.h"
#include "../Libraries/STD_types.h"
#include "../MCAL/GPIO.h"
#include "../MCAL/SysCtrl.h"
#include "../MCAL/SysTick.h"
#include "../MCAL/Interrupt.h"
#include "../MCAL/Timer.h"

extern void TIMER1A_User_Activity(void);

int main(void)
{
	SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF3_ENABLE);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODIR_R.B.DIR, GPIO_PF3_ENABLE);
	
	
	Init_RAM_Vector_Table();
	
	Set_TIMER1A_CallBack(TIMER1A_User_Activity);
	
	
	Init_GPT_Timer1A();
	
	/* Super Loop */
	while(1)
		{
			
		}
}

void TIMER1A_User_Activity(void)
{
	GPIO_PORTF_GPIODATA_R.B.DATA ^= GPIO_PF3_ENABLE;
	
	SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMICR_R.R, 0x1);
}
