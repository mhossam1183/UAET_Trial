/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <GPIO.h>
 *       Module:  -
 *
 *  Description:  <General-Purpose Input/Outputs definitions>     
 *  
 *********************************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Libraries/STD_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* GPIO PORTF base address */
#define GPIO_PORTF_BASE_ADDRESS             0x40025000

/* GPIO Data register fields definition */
typedef struct
{
	uint32_t DATA          :8;
	uint32_t Reserved      :24;
}GPIODATA_BF;

typedef union
{
	uint32_t     R;
	GPIODATA_BF  B;
}GPIODATA_Tag;

/* GPIODATA register offset */
#define GPIO_PORTF_GPIODATA_OFFSET      0x000

/* data register address mask (bits [9:2]) */
#define GPIO_PF3_BIT_MASK               0x20

/* PF3 pin enable */
#define GPIO_PF3_ENABLE                 0x8

#define GPIO_PORTF_GPIODATA_R          \
( * ( (volatile GPIODATA_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIODATA_OFFSET + GPIO_PF3_BIT_MASK) ) )

/* GPIO Direction fields definition */
typedef struct
{
	uint32_t DIR           :8;
	uint32_t Reserved      :24;
}GPIODIR_BF;

typedef union
{
	uint32_t     R;
	GPIODIR_BF  B;
}GPIODIR_Tag;

/* GPIODIR register offset */
#define GPIO_PORTF_GPIODIR_OFFSET     0x400

#define GPIO_PORTF_GPIODIR_R          \
( * ( (volatile GPIODIR_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIODIR_OFFSET) ) )

/* GPIO Digital Enable fields definition */
typedef struct
{
	uint32_t DEN           :8;
	uint32_t Reserved      :24;
}GPIODEN_BF;

typedef union
{
	uint32_t     R;
	GPIODEN_BF  B;
}GPIODEN_Tag;

/* GPIODEN register offset */
#define GPIO_PORTF_GPIODEN_OFFSET     0x51C

#define GPIO_PORTF_GPIODEN_R          \
( * ( (volatile GPIODEN_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIODEN_OFFSET) ) )
 
#endif  /* GPIO_H */

/**********************************************************************************************************************
 *  END OF FILE: GPIO.h
 *********************************************************************************************************************/
