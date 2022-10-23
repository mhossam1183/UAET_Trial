#include "../Libraries/Bit_Manipulation.h"
#include "../Libraries/STD_types.h"
#include "../MCAL/GPIO.h"
#include "../MCAL/SysCtrl.h"
#include "../MCAL/SysTick.h"
#include "../MCAL/Interrupt.h"

extern void SysTick_User_Activity(void);

int main(void)
{
	SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF3_ENABLE);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODIR_R.B.DIR, GPIO_PF3_ENABLE);
	
	
	Init_RAM_Vector_Table();
	
	Set_SysTick_CallBack(SysTick_User_Activity);
	
	SET_BIT_FIELD_VALUE(CORE_PPH_STCURRENT_R.B.CURRENT, 0x0);
	
	SET_BIT_FIELD_VALUE(CORE_PPH_STRELOAD_R.B.RELOAD, 15999999);
	
	SET_BIT(CORE_PPH_STCTRL_R.B.CLK_SRC);
	
	SET_BIT(CORE_PPH_STCTRL_R.B.INTEN);
	
	SET_BIT(CORE_PPH_STCTRL_R.B.ENABLE);
	
	/* Super Loop */
	while(1)
		{
			//SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODATA_R.B.DATA, GPIO_PF3_ENABLE);
		}
}

void SysTick_User_Activity(void)
{
	GPIO_PORTF_GPIODATA_R.B.DATA ^= GPIO_PF3_ENABLE;
}
