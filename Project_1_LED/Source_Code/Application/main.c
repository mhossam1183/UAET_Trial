#include "../Libraries/STD_types.h"
#include "../Libraries/Bit_Manipulation.h"
#include "../MCAL/Interrupt.h"
#include "../MCAL/Timer.h"
#include "../HAL/Led.h"
#include "../HAL/Push_Button.h"
#include "../MCAL/GPIO.h"

#define DUTY_CYCLE_START    0
#define DUTY_CYCLE_END      5

/* user function to be used as callback, for defining Timer exception handler */
extern void TIMER1A_User_Activity(void);

extern void GPIOF_User_Activity(void);

/* variable to control cycle resolution */
static uint8_t cycle_Count = 0;

static uint8_t duty_Cycle_Match = 1;

int main(void)
{
  /* Initialize GPIO pins to light green LED */
  Led_Init_Green();
	
	
  
  /* Initialize RAM version of vector table, and shift the VTABLE register to point to new RAM table */
  Intr_Init_RAM_Vector_Table();
  
  /* pass the user function as callback, to be assgined in the RAM vector table, in its correct index */
  Intr_Set_TIMER1A_CallBack(TIMER1A_User_Activity);
	
  /* Initialize GPTM "Timer 1 A" */
  Timer_Init_GPT_Timer1A();
  
	Intr_Set_GPIOF_Handler_CallBack(GPIOF_User_Activity);
	
	Push_Button_Init();
	
  /* Super Loop */
  while(1)
    {
      /* no instructions */
    }
}

/* user function definition */
void TIMER1A_User_Activity(void)
{
  if(cycle_Count == DUTY_CYCLE_START)
  {
    /* Green LED toggle */
    Led_On();
  }
	
  if(cycle_Count == duty_Cycle_Match)
  {
    /* Green LED toggle */
    Led_Off();
  }
  
  /* increament control variable */
  cycle_Count++;
  
  if(cycle_Count == DUTY_CYCLE_END)
  {    
    cycle_Count = 0;
  }
  
  /* clear GPTM "Timer 1 A" Interrupt flag */
  Timer_Clear_Timer1A_Flag();
}

/* SW1 is connected to PF4 pin, SW2 is connected to PF0. */
/* Both of them trigger PORTF falling edge interrupt */
void GPIOF_User_Activity(void)
{	
	

  if (GPIO_PORTF_GPIOMIS_R.B.MIS & GPIO_PF4_ENABLE) /* check if interrupt causes by PF4/SW1*/
    {   
			Led_On();
			SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOICR_R.B.IC, GPIO_PF4_ENABLE);
     } 
    else if (GPIO_PORTF_GPIOMIS_R.B.MIS & GPIO_PF0_ENABLE) /* check if interrupt causes by PF0/SW2 */
    {  
			Led_Off();
			SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOICR_R.B.IC, GPIO_PF0_ENABLE);
    }
}
