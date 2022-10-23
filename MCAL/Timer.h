/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Timer.h>
 *       Module:  -
 *
 *  Description:  <Timer definitions>     
 *  
 *********************************************************************************************************************/
#ifndef TIMER_H
#define TIMER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Libraries/STD_types.h"
#include "SysCtrl.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control */
typedef struct
{
	uint32_t R0              :1;
	uint32_t R1              :1;
	uint32_t R2              :1;
	uint32_t R3              :1;
	uint32_t R4              :1;
	uint32_t R5              :1;
	uint32_t Reserved        :26;
}RCGCTIMER_BF;

typedef union
{
	uint32_t     R;
	RCGCTIMER_BF  B;
}RCGCTIMER_Tag;

#define SYSTEM_CTRL_RCGCTIMER_OFFSET     0x604

#define SYSTEM_CTRL_RCGCTIMER_R          \
( * ( (volatile RCGCTIMER_Tag *) (SYSTEM_CTRL_BASE_ADDRESS + SYSTEM_CTRL_RCGCTIMER_OFFSET) ) )




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
extern void Init_GPT_Timer1A(void);

#endif  /* TIMER_H */

/**********************************************************************************************************************
 *  END OF FILE: Timer.h
 *********************************************************************************************************************/
