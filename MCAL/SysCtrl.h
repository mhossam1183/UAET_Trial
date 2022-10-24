/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <SysCtrl.h>
 *       Module:  -
 *
 *  Description:  <System Control & Clocks Signals definitions>     
 *  
 *********************************************************************************************************************/
#ifndef SYSCTRL_H
#define SYSCTRL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Libraries/STD_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* General-Purpose Input/Output Run Mode Clock Gating Control register fields definition */
typedef struct
{
	uint32_t PORTA_CLK     :1;
	uint32_t PORTB_CLK     :1;
	uint32_t PORTC_CLK     :1;
	uint32_t PORTD_CLK     :1;
	uint32_t PORTE_CLK     :1;
	uint32_t PORTF_CLK     :1;
	uint32_t Reserved      :26;
}RCGCGPIO_BF;

typedef union
{
	uint32_t     R;
	RCGCGPIO_BF  B;
}RCGCGPIO_Tag;

/* System Control base address */
#define SYSTEM_CTRL_BASE_ADDRESS        0x400FE000

/* RCGCGPIO register offset */
#define SYSTEM_CTRL_RCGCGPIO_OFFSET     0x608

#define SYSTEM_CTRL_RCGCGPIO_R          \
( * ( (volatile RCGCGPIO_Tag *) (SYSTEM_CTRL_BASE_ADDRESS + SYSTEM_CTRL_RCGCGPIO_OFFSET) ) )

#endif  /* SYSCTRL_H */

/**********************************************************************************************************************
 *  END OF FILE: SysCtrl.h
 *********************************************************************************************************************/
