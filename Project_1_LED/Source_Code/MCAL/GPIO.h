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

/* PF0 pin enable */
#define GPIO_PF0_ENABLE                 0x01

/* PF4 pin enable */
#define GPIO_PF4_ENABLE                 0x10

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

/* GPIO Lock (GPIOLOCK) register fields definition */

/* GPIOLOCK register offset */
#define GPIO_PORTF_GPIOLOCK_OFFSET     0x520

#define GPIO_PORTF_GPIOLOCK_R          \
( * ( (volatile uint32_t *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOLOCK_OFFSET) ) )

/* GPIO Commit (GPIOCR) register fields definition */
typedef struct
{
  uint32_t CR           :8;
  uint32_t Reserved      :24;
}GPIOCR_BF;

typedef union
{
  uint32_t     R;
  GPIOCR_BF  B;
}GPIOCR_Tag;

/* GPIOCR register offset */
#define GPIO_PORTF_GPIOCR_OFFSET     0x524

#define GPIO_PORTF_GPIOCR_R          \
( * ( (volatile GPIOCR_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOCR_OFFSET) ) )

/* GPIO Pull-Up Select (GPIOPUR) register fields definition */
typedef struct
{
  uint32_t PUE           :8;
  uint32_t Reserved      :24;
}GPIOPUR_BF;

typedef union
{
  uint32_t     R;
  GPIOPUR_BF  B;
}GPIOPUR_Tag;

/* GPIOPUR register offset */
#define GPIO_PORTF_GPIOPUR_OFFSET     0x510

#define GPIO_PORTF_GPIOPUR_R          \
( * ( (volatile GPIOPUR_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOPUR_OFFSET) ) )

/* GPIO Interrupt Sense (GPIOIS) register fields definition */
typedef struct
{
  uint32_t IS           :8;
  uint32_t Reserved      :24;
}GPIOIS_BF;

typedef union
{
  uint32_t     R;
  GPIOIS_BF  B;
}GPIOIS_Tag;

/* GPIOIS register offset */
#define GPIO_PORTF_GPIOIS_OFFSET     0x404

#define GPIO_PORTF_GPIOIS_R          \
( * ( (volatile GPIOIS_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOIS_OFFSET) ) )

/* GPIO Interrupt Both Edges (GPIOIBE) register fields definition */
typedef struct
{
  uint32_t IBE           :8;
  uint32_t Reserved      :24;
}GPIOIBE_BF;

typedef union
{
  uint32_t     R;
  GPIOIBE_BF  B;
}GPIOIBE_Tag;

/* GPIOIBE register offset */
#define GPIO_PORTF_GPIOIBE_OFFSET     0x408

#define GPIO_PORTF_GPIOIBE_R          \
( * ( (volatile GPIOIBE_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOIBE_OFFSET) ) )

/* GPIO Interrupt Event (GPIOIEV) register fields definition */
typedef struct
{
  uint32_t IEV           :8;
  uint32_t Reserved      :24;
}GPIOIEV_BF;

typedef union
{
  uint32_t     R;
  GPIOIEV_BF  B;
}GPIOIEV_Tag;

/* GPIOIEV register offset */
#define GPIO_PORTF_GPIOIEV_OFFSET     0x40C

#define GPIO_PORTF_GPIOIEV_R          \
( * ( (volatile GPIOIEV_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOIEV_OFFSET) ) )

/* GPIO Interrupt Clear (GPIOICR) register fields definition */
typedef struct
{
  uint32_t IC           :8;
  uint32_t Reserved      :24;
}GPIOICR_BF;

typedef union
{
  uint32_t     R;
  GPIOICR_BF  B;
}GPIOICR_Tag;

/* GPIOICR register offset */
#define GPIO_PORTF_GPIOICR_OFFSET     0x41C

#define GPIO_PORTF_GPIOICR_R          \
( * ( (volatile GPIOICR_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOICR_OFFSET) ) )

/* GPIO Interrupt Mask (GPIOIM) register fields definition */
typedef struct
{
  uint32_t IME           :8;
  uint32_t Reserved      :24;
}GPIOIM_BF;

typedef union
{
  uint32_t     R;
  GPIOIM_BF  B;
}GPIOIM_Tag;

/* GPIOIM register offset */
#define GPIO_PORTF_GPIOIM_OFFSET     0x410

#define GPIO_PORTF_GPIOIM_R          \
( * ( (volatile GPIOIM_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOIM_OFFSET) ) )

/* GPIO Masked Interrupt Status (GPIOMIS) register fields definition */
typedef struct
{
  uint32_t MIS           :8;
  uint32_t Reserved      :24;
}GPIOMIS_BF;

typedef union
{
  uint32_t     R;
  GPIOMIS_BF  B;
}GPIOMIS_Tag;

/* GPIOMIS register offset */
#define GPIO_PORTF_GPIOMIS_OFFSET     0x418

#define GPIO_PORTF_GPIOMIS_R          \
( * ( (volatile GPIOMIS_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIOMIS_OFFSET) ) )

#endif  /* GPIO_H */

/**********************************************************************************************************************
 *  END OF FILE: GPIO.h
 *********************************************************************************************************************/
