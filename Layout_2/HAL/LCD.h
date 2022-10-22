#ifndef LCD_H_
#define LCD_H_
#include "../GPIO/GPIO.h"
#include "../Timers/Timers.h"
#include <math.h>

#define RS (1)
#define RW (2)
#define EN (3)
#define D4 (4)
#define D5 (5)
#define D6 (6)
#define D7 (7)

#define FORCE_RESET           (0x3 )
#define FOUR_BITS_MODE        (0x2 )
#define SINGLE_LINE           (0x20)
#define DISPLAY_CLEAR         (0x01)
#define DISPLAY_CURSOR_ON     (0x0E)
#define DISPLAY_OFF           (0x08)
#define ENTRY_MODE            (0x06)
#define DISPLAY_ON_CURSOR_OFF (0x0C)
#define LEFT                  (0x10)
#define RIGHT                 (0x14)
#define DATA_REGISTER         (*((volatile uint8_t*) GPIO_DATA_R))
 
void LCD_init();
void LCD_command(uint8_t u8_command);
void LCD_data(uint8_t u8_data);
void LCD_printString(uint8_t* stream);
void LCD_printDigits(uint32_t u32_number);
void LCD_cursorMove(uint8_t);



#endif