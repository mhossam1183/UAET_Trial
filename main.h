#ifndef MAIN_H
#define MAIN_H

/* type defs */
typedef unsigned char          uint8_t;
typedef unsigned short int     uint16_t;
typedef unsigned long int      uint32_t;

/* bit values */
#define HIGH        0x1
#define LOW         0x0

/* helper macros */
#define SET_BIT(arg)                               arg |= HIGH
#define CLEAR_BIT(arg)                             arg &= LOW

#define SET_BIT_FIELD_VALUE(arg, value)            arg |= value

#define FORCE_BIT_FIELD_VALUE(arg, value)          arg = value
#define CLEAR_BIT_FIELD(arg)                       arg &= 0x00000000

/*-----------------------------------------------------------------------------------------------*/

/* General-Purpose Input/Output Run Mode Clock Gating Control */
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

#define SYSTEM_CTRL_BASE_ADDRESS        0x400FE000
#define SYSTEM_CTRL_RCGCGPIO_OFFSET     0x608

#define SYSTEM_CTRL_RCGCGPIO_R          ( * ( (volatile RCGCGPIO_Tag *) (SYSTEM_CTRL_BASE_ADDRESS + SYSTEM_CTRL_RCGCGPIO_OFFSET) ) )

/*-----------------------------------------------------------------------------------------------*/

/* GPIO PORTF base address */
#define GPIO_PORTF_BASE_ADDRESS             0x40025000

/* GPIO Data */
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

#define GPIO_PORTF_GPIODATA_OFFSET      0x000

#define GPIO_PF3_BIT_MASK               0x20

#define GPIO_PF3_ENABLE                 0x8

#define GPIO_PORTF_GPIODATA_R          ( * ( (volatile GPIODATA_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIODATA_OFFSET + GPIO_PF3_BIT_MASK) ) )

/* GPIO Direction */
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

#define GPIO_PORTF_GPIODIR_OFFSET     0x400

#define GPIO_PORTF_GPIODIR_R          ( * ( (volatile GPIODIR_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIODIR_OFFSET) ) )

/* GPIO Digital Enable */
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

#define GPIO_PORTF_GPIODEN_OFFSET     0x51C

#define GPIO_PORTF_GPIODEN_R          ( * ( (volatile GPIODEN_Tag *) (GPIO_PORTF_BASE_ADDRESS + GPIO_PORTF_GPIODEN_OFFSET) ) )

/*-----------------------------------------------------------------------------------------------*/

/* Core Peripherals base address */
#define CORE_PPH_BASE_ADDRESS             0xE000E000

/* SysTick Control Register */
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

#define CORE_PPH_STCTRL_OFFSET     0x010

#define CORE_PPH_STCTRL_R          ( * ( (volatile STCTRL_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_STCTRL_OFFSET) ) )

/* SysTick Reload Value Register */
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

#define CORE_PPH_STRELOAD_OFFSET     0x014

#define CORE_PPH_STRELOAD_R          ( * ( (volatile STRELOAD_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_STRELOAD_OFFSET) ) )

/* SysTick Current Value Register */
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

#define CORE_PPH_STCURRENT_OFFSET     0x018

#define CORE_PPH_STCURRENT_R          ( * ( (volatile STCURRENT_Tag *) (CORE_PPH_BASE_ADDRESS + CORE_PPH_STCURRENT_OFFSET) ) )

#endif  /* MAIN_H */
