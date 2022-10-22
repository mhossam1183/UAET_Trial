#include "./HAL/keypad.h"
#include "./MCAL/Timers.h"
#include "./HAL/LCD.h"

int main(void){
	
    uint8_t u8_number;
	keypad_init();
	LCD_init();
	while (1){
		
		if ( NO_BUTTON_PRESSED != keypad_scan() )
		{
			u8_number = keypad_scan();
			LCD_printDigits(u8_number);	
			TIMER0_msdelay(500);
		}
    }
}

