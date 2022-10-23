#include "./Libraries/Bit_Manipulation.h"
#include "./Libraries/STD_types.h"
#include "./MCAL/GPIO.h"
#include "./MCAL/SysCtrl.h"
#include "./MCAL/SysTick.h"
#include "./MCAL/Interrupt.h"

extern void SysTick_User_Activity(void);

extern void Time1A_1sec_delay(void);

extern void TIMER1A_Handler(void);

int main(void)
{
	SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF3_ENABLE);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODIR_R.B.DIR, GPIO_PF3_ENABLE);
	
	
	Init_RAM_Vector_Table();
	
//	Set_SysTick_CallBack(SysTick_User_Activity);
//	
//	
//	SET_BIT_FIELD_VALUE(CORE_PPH_STCURRENT_R.B.CURRENT, 0x0);
//	
//	SET_BIT_FIELD_VALUE(CORE_PPH_STRELOAD_R.B.RELOAD, 15999999);
//	
//	SET_BIT(CORE_PPH_STCTRL_R.B.CLK_SRC);
//	
//	SET_BIT(CORE_PPH_STCTRL_R.B.INTEN);
//	
//	SET_BIT(CORE_PPH_STCTRL_R.B.ENABLE);
	
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

/* Timer1 subtimer A interrupt service routine */
void TIMER1A_Handler(void)
{
	  if(TIMER1->MIS & 0x1)
		{
			GPIO_PORTF_GPIODATA_R.B.DATA ^= GPIO_PF3_ENABLE;
		}
		TIMER1->ICR = 0x1;          /* Timer1A timeout flag bit clears*/
}
void Time1A_1sec_delay(void)
{
SYSCTL->RCGCTIMER |= (1<<1);  /*enable clock Timer1 subtimer A in run mode */
TIMER1->CTL = 0; /* disable timer1 output */
TIMER1->CFG = 0x4; /*select 16-bit configuration option */
TIMER1->TAMR = 0x02; /*select periodic down counter mode of timer1 */
TIMER1->TAPR = 250-1; /* TimerA prescaler value */
TIMER1->TAILR = 64000-1 ; /* TimerA counter starting count down value  */
TIMER1->ICR = 0x1;          /* TimerA timeout flag bit clears*/
TIMER1->IMR |=(1<<0); /*enables TimerA time-out  interrupt mask */
TIMER1->CTL |= 0x01;        /* Enable TimerA module */
NVIC->ISER[0] |= (1<<21); /*enable IRQ21 */
}
