/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Interrupt.h>
 *       Module:  -
 *
 *  Description:  <Interrupt definitions>     
 *  
 *********************************************************************************************************************/
#ifndef INTERRUPT_H
#define INTERRUPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Libraries/STD_types.h"
#include "SysTick.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define VECTOR_TABLE_SIZE 155

/* Vector Table Offset */
typedef struct
{
	uint32_t Reserved      :10;
	uint32_t OFFSET        :22;
}VTABLE_BF;

typedef union
{
	uint32_t     R;
	VTABLE_BF  B;
}VTABLE_Tag;

#define CORE_PPH_VTABLE_OFFSET     0xD08

#define CORE_PPH_VTABLE_R          \
( * ( (volatile VTABLE_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_VTABLE_OFFSET) ) )

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
extern void Init_RAM_Vector_Table(void);

extern void Set_SysTick_CallBack(void (* Fun_Handler)(void));

extern void Set_Timer1A_CallBack(void (* Fun_Handler)(void));
 
#endif  /* INTERRUPT_H */

/**********************************************************************************************************************
 *  END OF FILE: Interrupt.h
 *********************************************************************************************************************/
