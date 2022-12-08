/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Led.c
 *        \brief  
 *
 *      \details  <Led definitions>
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Led.h"
#include "../Libraries/STD_types.h"
#include "../Libraries/Bit_Manipulation.h"
#include "../MCAL/GPIO.h"
#include "../MCAL/SysCtrl.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void Led_Init_Green(void)        
* \Description     : Init green Led                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Led_Init_Green(void)
{
  /* Enable and provide a clock to GPIO Port F in Run mode */
  SET_BIT(SYSTEM_CTRL_RCGCGPIO_R.B.PORTF_CLK);
  
  /* Enable port F => digital pin 3 */
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODEN_R.B.DEN, GPIO_PF3_ENABLE);
  
  /* port F => digital pin 3 set as output */
  SET_BIT_FIELD_VALUE(GPIO_PORTF_GPIODIR_R.B.DIR, GPIO_PF3_ENABLE);
}

/******************************************************************************
* \Syntax          : void Led_On(void)        
* \Description     : green Led on                                   
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Led_On(void)
{
  /* Set PF3 pin */
  FORCE_BIT_FIELD_VALUE(GPIO_PORTF_GPIODATA_R.B.DATA, GPIO_PF3_ENABLE);
}

/******************************************************************************
* \Syntax          : void Led_Off(void)        
* \Description     : green Led Off                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Led_Off(void)
{
  /* clear PF3 pin */
  FORCE_BIT_FIELD_VALUE(GPIO_PORTF_GPIODATA_R.B.DATA, LOW);
}

/******************************************************************************
* \Syntax          : void Led_Toggle(void)        
* \Description     : green Led Toggle                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Led_Toggle(void)
{
  /* toggle PF3 pin */
  GPIO_PORTF_GPIODATA_R.B.DATA ^= GPIO_PF3_ENABLE;
}

/**********************************************************************************************************************
 *  END OF FILE: Led.c
 *********************************************************************************************************************/
