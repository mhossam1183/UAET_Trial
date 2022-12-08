/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Push_Button.c
 *        \brief  
 *
 *      \details  <Push_Button definitions>
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Push_Button.h"
#include "../Libraries/STD_types.h"
#include "../Libraries/Bit_Manipulation.h"
#include "../MCAL/GPIO.h"
#include "../MCAL/SysCtrl.h"
#include "../MCAL/Timer.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void Push_Button_Init(void)        
* \Description     : Init Push_Button                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Push_Button_Init(void)
{
  /* Enable and provide a clock to GPIO Port F in Run mode */
  SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
  
  
  /* unlock commit register */
  FORCE_BIT_FIELD_VALUE(GPIO_PORTF_GPIOLOCK_R, 0x4C4F434B);
  
  /* Enable configuration of PORTF critical registers */
  FORCE_BIT_FIELD_VALUE(GPIO_PORTF_GPIOCR_R.B.CR, 0x01);
  
  /* lock commit register */
  FORCE_BIT_FIELD_VALUE(GPIO_PORTF_GPIOLOCK_R, 0x0);
  
  
  /* Enable port F => digital pin 0 & pin 4 */
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF0_ENABLE);
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF4_ENABLE);
  
  /* port F => digital pin 0 & pin 4 set as input */
  GPIO_PORTF_GPIODIR_R.B.DIR &= (~GPIO_PF0_ENABLE);
  GPIO_PORTF_GPIODIR_R.B.DIR &= (~GPIO_PF4_ENABLE);
  
  /* enable pull up resistor for port F => digital pin 0 & pin 4 */
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOPUR_R.B.PUE, GPIO_PF0_ENABLE);
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOPUR_R.B.PUE, GPIO_PF4_ENABLE);
  
  
  /* port F => make pin 0 & pin 4 edge sensitive */
  GPIO_PORTF_GPIOIS_R.B.IS &= (~GPIO_PF0_ENABLE);
  GPIO_PORTF_GPIOIS_R.B.IS &= (~GPIO_PF4_ENABLE);
  
  /* port F => make pin 0 & pin 4 Interrupt controlled by GPIO Interrupt Event */
  GPIO_PORTF_GPIOIBE_R.B.IBE &= (~GPIO_PF0_ENABLE);
  GPIO_PORTF_GPIOIBE_R.B.IBE &= (~GPIO_PF4_ENABLE);
  
  /* port F => make pin 0 & pin 4 falling edge trigger Interrupt */
  GPIO_PORTF_GPIOIEV_R.B.IEV &= (~GPIO_PF0_ENABLE);
  GPIO_PORTF_GPIOIEV_R.B.IEV &= (~GPIO_PF4_ENABLE);
  
  /* clear prior interrupt for port F => digital pin 0 & pin 4 */
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOICR_R.B.IC, GPIO_PF0_ENABLE);
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOICR_R.B.IC, GPIO_PF4_ENABLE);
  
  /* interrupt sent to interrupt controller for port F => digital pin 0 & pin 4 */
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOIM_R.B.IME, GPIO_PF0_ENABLE);
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIOIM_R.B.IME, GPIO_PF4_ENABLE);
  
  /* IRQ30 (GPIOF_Handler) interrupt is enabled */
  NVIC_EN0_R.B.INT |= (0x1 << 30);
}

/**********************************************************************************************************************
 *  END OF FILE: Push_Button.c
 *********************************************************************************************************************/
