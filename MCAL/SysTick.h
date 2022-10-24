/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <SysTick.h>
 *       Module:  -
 *
 *  Description:  <System Timer (SysTick) Register definitions>     
 *  
 *********************************************************************************************************************/
#ifndef SYSTICK_H
#define SYSTICK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Libraries/STD_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Core Peripherals base address */
#define CORE_PPH_BASE_ADDRESS             0xE000E000

/* SysTick Control Register register fields definition */
typedef struct
{
	uint32_t ENABLE        :1;
	uint32_t INTEN         :1;
	uint32_t CLK_SRC       :1;
	uint32_t Reserved      :13;
	uint32_t COUNT         :1;
	uint32_t Reserved_2      :15;
}STCTRL_BF;

typedef union
{
	uint32_t     R;
	STCTRL_BF  B;
}STCTRL_Tag;

/* STCTRL register offset */
#define CORE_PPH_STCTRL_OFFSET     0x010

#define CORE_PPH_STCTRL_R          \
( * ( (volatile STCTRL_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_STCTRL_OFFSET) ) )

/* SysTick Reload Value register fields definition */
typedef struct
{
	uint32_t RELOAD        :24;
	uint32_t Reserved      :8;
}STRELOAD_BF;

typedef union
{
	uint32_t     R;
	STRELOAD_BF  B;
}STRELOAD_Tag;

/* STRELOAD register offset */
#define CORE_PPH_STRELOAD_OFFSET     0x014

#define CORE_PPH_STRELOAD_R          \
( * ( (volatile STRELOAD_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_STRELOAD_OFFSET) ) )

/* SysTick Current Value register fields definition */
typedef struct
{
	uint32_t CURRENT        :24;
	uint32_t Reserved      :8;
}STCURRENT_BF;

typedef union
{
	uint32_t     R;
	STCURRENT_BF  B;
}STCURRENT_Tag;

/* STCURRENT register offset */
#define CORE_PPH_STCURRENT_OFFSET     0x018

#define CORE_PPH_STCURRENT_R          \
( * ( (volatile STCURRENT_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_STCURRENT_OFFSET) ) )

#endif  /* SYSTICK_H */

/**********************************************************************************************************************
 *  END OF FILE: SysTick.h
 *********************************************************************************************************************/
