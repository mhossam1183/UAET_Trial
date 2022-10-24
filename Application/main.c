#include "../MCAL/Interrupt.h"
#include "../MCAL/Timer.h"
#include "../HAL/Led.h"

extern void TIMER1A_User_Activity(void);

static unsigned char counter = 0;

int main(void)
{
  Led_Init_Green();
  
  Intr_Init_RAM_Vector_Table();
  
  Intr_Set_TIMER1A_CallBack(TIMER1A_User_Activity);
  
  Timer_Init_GPT_Timer1A();
  
  /* Super Loop */
  while(1)
    {
      
    }
}

void TIMER1A_User_Activity(void)
{
	if((counter % 4) == 0)
	{
    Led_Toggle();
	}
	
	counter++;
	
	Timer_Clear_Timer1A_Flag();
}
