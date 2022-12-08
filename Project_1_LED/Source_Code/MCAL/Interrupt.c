/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Interrupt.c
 *        \brief  
 *
 *      \details  <Interrupt definitions>
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Interrupt.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
/* index of exception handlers in the vector table, based on the "tm4c123gh6pm" data sheet */
#define SYSTICK_IRQ_NUMBER        15

#define TIMER1A_IRQ_NUMBER        37

#define GPIOF_IRQ_NUMBER        46

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
/* Allocate RAM version of vector table.
   Address will be assigned to "Vector Table Offset" register (must be aligned on a 1024-byte boundary) */
static void (* Vector_Table_RAM[VECTOR_TABLE_SIZE])(void) __attribute__((aligned(1024)));

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void Intr_Init_RAM_Vector_Table(void)        
* \Description     : Initialize RAM version of vector table,
*                    and shift the VTABLE register to point to new RAM table.                                  
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Intr_Init_RAM_Vector_Table(void)
{
    /* Check VTABLE register was updated already */ 
  if(CORE_PPH_VTABLE_R.R != (uint32_t)Vector_Table_RAM)
  {
    /* save initial VTABLE register value */
    uint32_t Current_VT_Offset = (uint32_t)CORE_PPH_VTABLE_R.R;
    uint32_t Loop_index = 0;
    
    /* copy the content of initial "Flash version" vector table to new RAM table */
    while(Loop_index < VECTOR_TABLE_SIZE)
    {
      Vector_Table_RAM[Loop_index] = (void (*)(void)) (Current_VT_Offset + (Loop_index * sizeof(uint32_t)));
      
      Loop_index++;
    }
    
    /* assign the address of the new RAM table to the VTABLE register */
    CORE_PPH_VTABLE_R.R = (uint32_t)Vector_Table_RAM;
  }
}

/******************************************************************************
* \Syntax          : void Intr_Set_SysTick_CallBack(void (* Fun_Handler)(void))        
* \Description     : pass the user function(for defining systick exception handler) as callback,
*                    to be assgined in the RAM vector table, in its correct IRQ index.                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Intr_Set_SysTick_CallBack(void (* Fun_Handler)(void))
{
  Vector_Table_RAM[SYSTICK_IRQ_NUMBER] = Fun_Handler;
}

/******************************************************************************
* \Syntax          : void Intr_Set_TIMER1A_CallBack(void (* Fun_Handler)(void))        
* \Description     : pass the user function(for defining "Timer 1 A" exception handler) as callback,
*                    to be assgined in the RAM vector table, in its correct IRQ index.                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Intr_Set_TIMER1A_CallBack(void (* Fun_Handler)(void))
{
  Vector_Table_RAM[TIMER1A_IRQ_NUMBER] = Fun_Handler;
}

/******************************************************************************
* \Syntax          : void Intr_Set_GPIOF_Handler_CallBack(void (* Fun_Handler)(void))        
* \Description     : pass the user function(for defining "GPIOF_Handler" exception handler) as callback,
*                    to be assgined in the RAM vector table, in its correct IRQ index.                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Intr_Set_GPIOF_Handler_CallBack(void (* Fun_Handler)(void))
{
  Vector_Table_RAM[GPIOF_IRQ_NUMBER] = Fun_Handler;
}

/**********************************************************************************************************************
 *  END OF FILE: Interrupt.c
 *********************************************************************************************************************/
