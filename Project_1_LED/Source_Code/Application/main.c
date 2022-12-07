#include "../Libraries/STD_types.h"
#include "../Libraries/Bit_Manipulation.h"
#include "../MCAL/Interrupt.h"
#include "../MCAL/Timer.h"
#include "../HAL/Led.h"

/* user function to be used as callback, for defining Timer exception handler */
extern void TIMER1A_User_Activity(void);

/* variable to carry user defined cycle time in seconds */
static uint32_t user_cycle_Sec = 0;

/* variable to control cycle resolution */
static uint32_t cycle_count = 0;

int main(void)
{
  /* Initialize GPIO pins to light green LED */
  Led_Init_Green();
  
  /* Initialize RAM version of vector table, and shift the VTABLE register to point to new RAM table */
  Intr_Init_RAM_Vector_Table();
  
  /* pass the user function as callback, to be assgined in the RAM vector table, in its correct index */
  Intr_Set_TIMER1A_CallBack(TIMER1A_User_Activity);
  
  /* set cycle time in seconds (must be greater than 0) */
  FORCE_BIT_FIELD_VALUE(user_cycle_Sec, 3);
  
  /* Initialize GPTM "Timer 1 A" */
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
  /* operation to control cycle resolution */
  //if((cycle_count % (user_cycle_Sec * 2)) == 0)
  {
    /* Green LED toggle */
    Led_Toggle();
  }
  
  /* increament control variable */
  cycle_count++;
  
  /* clear GPTM "Timer 1 A" Interrupt flag */
  Timer_Clear_Timer1A_Flag();
}
