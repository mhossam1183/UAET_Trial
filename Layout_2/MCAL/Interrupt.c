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
#define SYSTICK_IRQ_NUMBER        15

#define TIMER1A_IRQ_NUMBER        37

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static void (* Vector_Table_RAM[VECTOR_TABLE_SIZE])(void) __attribute__((aligned(1024)));

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : void Init_RAM_Vector_Table(void)        
* \Description     : init ram vtable                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Init_RAM_Vector_Table(void)
{
	if(CORE_PPH_VTABLE_R.R != (uint32_t)Vector_Table_RAM)
	{
		uint32_t Current_VT_Offset = (uint32_t)CORE_PPH_VTABLE_R.R;
		uint32_t Loop_index = 0;
		
		while(Loop_index < VECTOR_TABLE_SIZE)
		{
			Vector_Table_RAM[Loop_index] = (void (*)(void)) (Current_VT_Offset + (Loop_index * sizeof(uint32_t)));
			
			Loop_index++;
		}
		
		CORE_PPH_VTABLE_R.R = (uint32_t)Vector_Table_RAM;
	}
}

/******************************************************************************
* \Syntax          : void Init_RAM_Vector_Table(void)        
* \Description     : init ram vtable                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Set_SysTick_CallBack(void (* Fun_Handler)(void))
{
	Vector_Table_RAM[SYSTICK_IRQ_NUMBER] = Fun_Handler;
}

/******************************************************************************
* \Syntax          : void Init_RAM_Vector_Table(void)        
* \Description     : init ram vtable                                    
*                                                                             
* \Sync\Async      : Asynchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void Set_TIMER1A_CallBack(void (* Fun_Handler)(void))
{
	Vector_Table_RAM[TIMER1A_IRQ_NUMBER] = Fun_Handler;
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
/*Std_ReturnType FunctionName(AnyType parameterName)
{
	
	
}*/

/**********************************************************************************************************************
 *  END OF FILE: Interrupt.c
 *********************************************************************************************************************/