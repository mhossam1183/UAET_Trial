/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Timer.c
 *        \brief  
 *
 *      \details  <GPTM Timer definitions>
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Timer.h"
#include "../Libraries/Bit_Manipulation.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void Timer_Init_GPT_Timer1A(void)        
* \Description     : Initialize GPTM "Timer 1 A" to a 500 ms cycle                                   
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Timer_Init_GPT_Timer1A(void)
{
  /* Enable and provide a clock to 16/32-bit general-purpose timer module 1 in Run mode */
  SET_BIT(SYSTEM_CTRL_RCGCTIMER_R.B.R1);
  
  /* Timer A is disabled, as well as other timers */
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMCTL_R.R, 0x0);
  
  /* For a 16/32-bit timer, the 16-bit timer configuration is selected */
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMCFG_R.R, 0x4);
  
  /* GPTM Timer A is set to Periodic Timer mode */
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMTAMR_R.R, 0x2);
  
  /* Timer A Prescale & Interval Load are set for 1 second cycle */
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMTAPR_R.R, ( 250 - 1 ));
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMTAILR_R.R, ( 64000 - 1 ));
  
  /* Clear GPTM Timer A Time-Out Interrupt */
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMICR_R.R, 0x1);
  
  /* GPTM Timer A Time-Out Interrupt is enabled */
  SET_BIT(GPTM_TIMER1_GPTMIMR_R.B.TATOIM);
  
  /* Timer A is enabled, other timers remain disabled */
  SET_BIT(GPTM_TIMER1_GPTMCTL_R.B.TAEN);
  
  /* "Timer 1 A" interrupt is enabled */
  NVIC_EN0_R.B.INT |= (0x1 << 21);
}

/******************************************************************************
* \Syntax          : void Timer_Clear_Timer1A_Flag(void)        
* \Description     : clear GPTM "Timer 1 A" Interrupt flag                                  
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Timer_Clear_Timer1A_Flag(void)
{
  SET_BIT_FIELD_VALUE(GPTM_TIMER1_GPTMICR_R.R, 0x1);
}

/**********************************************************************************************************************
 *  END OF FILE: Timer.c
 *********************************************************************************************************************/
