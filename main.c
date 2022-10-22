#include "./Libraries/Bit_Manipulation.h"
#include "./Libraries/STD_types.h"
#include "./MCAL/GPIO.h"
#include "./MCAL/SysCtrl.h"
#include "./MCAL/SysTick.h"
#include "./MCAL/Timer.h"

#define Vectors_Size 155

extern void Function_1(void);

void Function_1(void)
{
	GPIO_PORTF_GPIODATA_R.B.DATA ^= GPIO_PF3_ENABLE;
}

static uint32_t Vector_Table_RAM[1] __attribute__((aligned(1024)));

static uint32_t * var1 = 0;

static uint32_t * var2 = 0;

int main(void)
{
	var1 = (uint32_t *)(CORE_PPH_VTABLE_R.R + 0x003C);
	
	CORE_PPH_VTABLE_R.R = (uint32_t)&Vector_Table_RAM;
	
	var2 = (uint32_t *)(CORE_PPH_VTABLE_R.R + 0x003C);
	
	*var2 = &Function_1;
	
	SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF3_ENABLE);
	
	SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODIR_R.B.DIR, GPIO_PF3_ENABLE);
	
	
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
