#include "../MCAL/Interrupt.h"
#include "../MCAL/Timer.h"
#include "../HAL/Led.h"

/* user function to be used as callback, for defining Timer exception handler */
extern void TIMER1A_User_Activity(void);

int main(void)
{
  /* Initialize GPIO pins to light green LED */
  Led_Init_Green();
  
  /* Initialize RAM version of vector table, and shift the VTABLE register to point to new RAM table */
  Intr_Init_RAM_Vector_Table();
  
  /* pass the user function as callback, to be assgined in the RAM vector table, in its correct index */
  Intr_Set_TIMER1A_CallBack(TIMER1A_User_Activity);
  
  /* Initialize GPTM "Timer 1 A" to a 500 ms cycle */
  Timer_Init_GPT_Timer1A();
  
  /* Super Loop */
  while(1)
    {
      /* no instructions */
    }
}

/* user function definition */
void TIMER1A_User_Activity(void)
{
	/* Green LED toggle */
	Led_Toggle();
	
	/* clear GPTM "Timer 1 A" Interrupt flag */
	Timer_Clear_Timer1A_Flag();
}