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
/* "16/32-Bit General-Purpose Timer Run Mode Clock Gating Control" register fields definition */
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

/* RCGCTIMER register offset */
#define SYSTEM_CTRL_RCGCTIMER_OFFSET     0x604

#define SYSTEM_CTRL_RCGCTIMER_R          \
( * ( (volatile RCGCTIMER_Tag *) (SYSTEM_CTRL_BASE_ADDRESS + SYSTEM_CTRL_RCGCTIMER_OFFSET) ) )

/*------------------------------------------------------------------------------------------------*/
/* 16/32-bit Timer 1 base address */
#define GPTM_TIMER1_BASE_ADDRESS          0x40031000

/* GPTM Control register fields definition */
typedef struct
{
  uint32_t TAEN                   :1;
  uint32_t TASTALL                :1;
  uint32_t TAEVENT                :2;
  uint32_t RTCEN                  :1;
  uint32_t TAOTE                  :1;
  uint32_t TAPWML                 :1;
  uint32_t Reserved1              :1;
  uint32_t TBEN                   :1;
  uint32_t TBSTALL                :1;
  uint32_t TBEVENT                :2;
  uint32_t Reserved2              :1;
  uint32_t TBOTE                  :1;
  uint32_t TBPWML                 :1;
  uint32_t Reserved3              :17;
}GPTMCTL_BF;

typedef union
{
  uint32_t     R;
  GPTMCTL_BF  B;
}GPTMCTL_Tag;

/* GPTMCTL register offset */
#define GPTM_TIMER1_GPTMCTL_OFFSET     0x00C

#define GPTM_TIMER1_GPTMCTL_R          \
( * ( (volatile GPTMCTL_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMCTL_OFFSET) ) )

/* GPTM Configuration register fields definition */
typedef struct
{
  uint32_t GPTMCFG                   :3;
  uint32_t Reserved                  :29;
}GPTMCFG_BF;

typedef union
{
  uint32_t     R;
  GPTMCFG_BF  B;
}GPTMCFG_Tag;

/* GPTMCFG register offset */
#define GPTM_TIMER1_GPTMCFG_OFFSET     0x000

#define GPTM_TIMER1_GPTMCFG_R          \
( * ( (volatile GPTMCFG_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMCFG_OFFSET) ) )

/* GPTM Timer A Mode register fields definition */
typedef struct
{
  uint32_t TAMR                      :2;
  uint32_t TACMR                     :1;
  uint32_t TAAMS                     :1;
  uint32_t TACDIR                    :1;
  uint32_t TAMIE                     :1;
  uint32_t TAWOT                     :1;
  uint32_t TASNAPS                   :1;
  uint32_t TAILD                     :1;
  uint32_t TAPWMIE                   :1;
  uint32_t TAMRSU                    :1;
  uint32_t TAPLO                     :1;
  uint32_t Reserved                  :20;
}GPTMTAMR_BF;

typedef union
{
  uint32_t     R;
  GPTMTAMR_BF  B;
}GPTMTAMR_Tag;

/* GPTMTAMR register offset */
#define GPTM_TIMER1_GPTMTAMR_OFFSET     0x004

#define GPTM_TIMER1_GPTMTAMR_R          \
( * ( (volatile GPTMTAMR_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMTAMR_OFFSET) ) )

/* GPTM Timer A Prescale register fields definition */
typedef struct
{
  uint32_t TAPSR                     :8;
  uint32_t TAPSRH                    :8;
  uint32_t Reserved                  :16;
}GPTMTAPR_BF;

typedef union
{
  uint32_t     R;
  GPTMTAPR_BF  B;
}GPTMTAPR_Tag;

/* GPTMTAPR register offset */
#define GPTM_TIMER1_GPTMTAPR_OFFSET     0x038

#define GPTM_TIMER1_GPTMTAPR_R          \
( * ( (volatile GPTMTAPR_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMTAPR_OFFSET) ) )

/* GPTM Timer A Interval Load register fields definition */
typedef struct
{
  uint32_t TAILR                   :32;
}GPTMTAILR_BF;

typedef union
{
  uint32_t     R;
  GPTMTAILR_BF  B;
}GPTMTAILR_Tag;

/* GPTMTAILR register offset */
#define GPTM_TIMER1_GPTMTAILR_OFFSET     0x028

#define GPTM_TIMER1_GPTMTAILR_R          \
( * ( (volatile GPTMTAILR_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMTAILR_OFFSET) ) )

/* GPTM Interrupt Clear register fields definition */
typedef struct
{
  uint32_t TATOCINT                  :1;
  uint32_t CAMCINT                   :1;
  uint32_t CAECINT                   :1;
  uint32_t RTCCINT                   :1;
  uint32_t TAMCINT                   :1;
  uint32_t Reserved2                 :3;
  uint32_t TBTOCINT                  :1;
  uint32_t CBMCINT                   :1;
  uint32_t CBECINT                   :1;
  uint32_t TBMCINT                   :1;
  uint32_t Reserved1                 :4;
  uint32_t WUECINT                   :1;
  uint32_t Reserved                  :15;
}GPTMICR_BF;

typedef union
{
  uint32_t     R;
  GPTMICR_BF  B;
}GPTMICR_Tag;

/* GPTMICR register offset */
#define GPTM_TIMER1_GPTMICR_OFFSET     0x024

#define GPTM_TIMER1_GPTMICR_R          \
( * ( (volatile GPTMICR_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMICR_OFFSET) ) )

/* GPTM Interrupt Mask register fields definition */
typedef struct
{
  uint32_t TATOIM                  :1;
  uint32_t CAMIM                   :1;
  uint32_t CAEIM                   :1;
  uint32_t RTCIM                   :1;
  uint32_t TAMIM                   :1;
  uint32_t Reserved2               :3;
  uint32_t TBTOIM                  :1;
  uint32_t CBMIM                   :1;
  uint32_t CBEIM                   :1;
  uint32_t TBMIM                   :1;
  uint32_t Reserved1               :4;
  uint32_t WUEIM                   :1;
  uint32_t Reserved                :15;
}GPTMIMR_BF;

typedef union
{
  uint32_t     R;
  GPTMIMR_BF  B;
}GPTMIMR_Tag;

/* GPTMIMR register offset */
#define GPTM_TIMER1_GPTMIMR_OFFSET     0x018

#define GPTM_TIMER1_GPTMIMR_R          \
( * ( (volatile GPTMIMR_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMIMR_OFFSET) ) )

/* GPTM Masked Interrupt Status register fields definition */
typedef struct
{
  uint32_t TATOMIS                  :1;
  uint32_t CAMMIS                   :1;
  uint32_t CAEMIS                   :1;
  uint32_t RTCMIS                   :1;
  uint32_t TAMMIS                   :1;
  uint32_t Reserved2               :3;
  uint32_t TBTOMIS                  :1;
  uint32_t CBMMIS                   :1;
  uint32_t CBEMIS                   :1;
  uint32_t TBMMIS                   :1;
  uint32_t Reserved1               :4;
  uint32_t WUEMIS                   :1;
  uint32_t Reserved                :15;
}GPTMMIS_BF;

typedef union
{
  uint32_t     R;
  GPTMMIS_BF  B;
}GPTMMIS_Tag;

/* GPTMMIS register offset */
#define GPTM_TIMER1_GPTMMIS_OFFSET     0x020

#define GPTM_TIMER1_GPTMMIS_R          \
( * ( (volatile GPTMMIS_Tag *) (GPTM_TIMER1_BASE_ADDRESS + GPTM_TIMER1_GPTMMIS_OFFSET) ) )

/*------------------------------------------------------------------------------------------------*/
/* NVIC Register base address */
#define NVIC_BASE_ADDRESS         0xE000E000

/* "Interrupt 0-31 Set Enable" register fields definition */
typedef struct
{
  uint32_t INT                   :32;
}EN0_BF;

typedef union
{
  uint32_t     R;
  EN0_BF  B;
}EN0_Tag;

/* NVIC_EN0 register offset */
#define NVIC_EN0_OFFSET     0x100

#define NVIC_EN0_R          \
( * ( (volatile EN0_Tag *) (NVIC_BASE_ADDRESS + NVIC_EN0_OFFSET) ) )
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
extern void Timer_Init_GPT_Timer1A(void);

extern void Timer_Clear_Timer1A_Flag(void);

#endif  /* TIMER_H */

/**********************************************************************************************************************
 *  END OF FILE: Timer.h
 *********************************************************************************************************************/
