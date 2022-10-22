#ifndef GPIO_H_
#define GPIO_H_

#include "../Libraries/ATMEGA32.h"
#include "../Libraries/BIT_manipulation.h"
#include "../Libraries/ERROR_states.h"

/****************************************************************************/
/*                                                                          */
/*                            User Defined Macros                           */
/*                                                                          */
/****************************************************************************/
 
#define A                     (0)
#define B                     (3)
#define C                     (6)
#define D                     (9)
#define OUTPUT                (1)
#define INPUT                 (0)
#define HIGH                  (1)
#define LOW                   (0)
#define LEAST_SIGNIFICANT_BIT (0)
#define MOST_SIGNIFICANT_BIT  (7)

/****************************************************************************/
/*                                                                          */
/*                            Functions Prototypes                          */
/*                                                                          */
/****************************************************************************/

uint8_t GPIO_setHigh(uint8_t u8_port, uint8_t u8_bit);
uint8_t GPIO_toggle(uint8_t u8_port, uint8_t u8_bit);
uint8_t GPIO_dir(uint8_t u8_port, uint8_t u8_bit, uint8_t u8_mode);
uint8_t GPIO_setLow(uint8_t u8_port, uint8_t u8_bit);
uint8_t GPIO_read(uint8_t u8_port, uint8_t u8_bit);


#endif 