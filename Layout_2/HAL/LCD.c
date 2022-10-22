#include "LCD.h"

void LCD_init(){
	
	/*****************************************************************/
	/* This delay is a recommended by manufacturer after powering up */
	/*****************************************************************/
	TIMER0_msdelay(100);
	
	/*******************************************************/
	/* Configuring LCD Control and Data pins to be outputs */
	/*******************************************************/
	GPIO_dir(A,RS,OUTPUT);
	GPIO_dir(A,RW,OUTPUT);
	GPIO_dir(A,EN,OUTPUT);
	GPIO_dir(A,D4,OUTPUT);
	GPIO_dir(A,D5,OUTPUT);
	GPIO_dir(A,D6,OUTPUT);
	GPIO_dir(A,D7,OUTPUT);
	TIMER0_msdelay(100);
	
	/***********************************/
	/* Initial Commands                */
	/***********************************/    
	LCD_command(FORCE_RESET);           /*************************************************************************/
	TIMER0_msdelay(10);                 /*                                                                       */
	LCD_command(FORCE_RESET);           /*                                                                       */
	TIMER0_msdelay(10);                 /* These three repetitive commands are used to effectively reset the LCD */
	LCD_command(FORCE_RESET);           /*                                                                       */
	TIMER0_msdelay(10);                 /*                                                                       */ 
	                                    /*************************************************************************/
	
	LCD_command(FOUR_BITS_MODE);        /**************************************************************************/
	TIMER0_msdelay(10);                 /*                       Enable 4-BITS Mode                               */
	                                    /**************************************************************************/
	
	LCD_command(DISPLAY_OFF);           /**************************************************************************/
	TIMER0_msdelay(10);                 /*                       Turn Display Off                                 */
	                                    /**************************************************************************/
	
	LCD_command(DISPLAY_CLEAR);         /**************************************************************************/      
	TIMER0_msdelay(10);                 /*                       Clearing Display                                 */
	                                    /**************************************************************************/
	
	LCD_command(ENTRY_MODE);            /**************************************************************************/  
	TIMER0_msdelay(10);                 /*                 Enable Cursor Increment During Entry                   */
	                                    /**************************************************************************/
	
	LCD_command(DISPLAY_ON_CURSOR_OFF); /**************************************************************************/
	TIMER0_msdelay(10);                 /*          Turn On Display and Turn Off Cursor                           */
	                                    /**************************************************************************/        
/***************************************/
/*        End of Initialization        */
/***************************************/
}

void LCD_command(uint8_t u8_command){
		
	/**************************************************************/
	/* Since we are using 4-bit mode, we are only allowed         */
	/* to send 4 bits of data at a time. Therefore, we will       */
	/* partition the 8 bit data into 2 partitions; Higher nipple  */
	/* and Lower nipple and then send each of them respectively   */
	/**************************************************************/ 
	
	/*************************/
	/* Sending higher nipple */
	/*************************/
	DATA_REGISTER =  (DATA_REGISTER & (0x0F)) |  (u8_command & (0xF0));
	GPIO_setLow(A,RS);
	GPIO_setHigh(A,EN);
	TIMER0_msdelay(10);
	GPIO_setLow(A,EN);
	TIMER0_msdelay(10);
	
	/************************/
	/* Sending lower nipple */
	/************************/
	DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_command << 4);
	GPIO_setHigh(A,EN);              /**********************************************************/
	TIMER0_msdelay(10);              /*  Here we set EN pin to high when reading               */
	GPIO_setLow(A,EN);               /*  and then set it low to latch the input data.          */
	TIMER0_msdelay(10);              /*  Delays are used to give the LCD needed processing time*/     
                                     /**********************************************************/
}

void LCD_data(uint8_t u8_data){
		
	/*************************/
	/* Sending higher nipple */
	/*************************/
	DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_data & (0xF0));
	GPIO_setHigh(A,RS);
	GPIO_setHigh(A,EN);
	TIMER0_msdelay(10);
	GPIO_setLow(A,EN);
	TIMER0_msdelay(10);
	
	/************************/
	/* Sending lower nipple */
	/************************/
	DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_data << 4);
	GPIO_setHigh(A,EN);
	TIMER0_msdelay(10);
	GPIO_setLow(A,EN);
	TIMER0_msdelay(10); 
}

/******************************************************/
/*    This function is used only to print a string    */
/******************************************************/

void LCD_printString(uint8_t* stream){
	
	uint8_t u8_index;
	
	for (u8_index = 0 ; stream[u8_index] != 0 ; u8_index++){
		
		LCD_data(stream[u8_index]);
	}
}

/******************************************************/
/*      This function is used only to print a digit   */
/******************************************************/

void LCD_printDigits(uint32_t u32_number){
	
	volatile uint8_t  u8_temp;
	volatile uint8_t  u8_weight;
	volatile uint8_t  u8_data;
	volatile uint8_t  u8_digits;
	volatile f32_t    f32_temp;
	                                                     /*******************************************************************************/
	u8_weight = log10(u32_number);                       /* 1 - Calculating the weight of the most significant digit                    */
	u8_digits = (u8_weight + 1);                         /* 2 - Adding 1 to weight to specify number of digits in present               */ 
	u8_temp   = (u32_number / pow(10,u8_weight));        /* 3 - Isolating the Most significant digit by placing it before decimal point */
	f32_temp  = ((u32_number*1.0) / pow(10,u8_weight));  /* 4 - Storing the floating point number to be used afterwards                 */ 
	                                                     /*******************************************************************************/
	do {
		                                                 /****************************************************************************************/
		u8_data  = (u8_temp | (3 << 4));                 /* 1 - Converting the number in u8_temp to hex value of the number's ascii code         */ 
		LCD_data(u8_data);                               /* 2 - Sending the hex value to LCD to get printed                                      */
		u8_digits--;                                     /* 3 - Now that a digit has been printed, the remaining digits in present will decrease */ 
		f32_temp = f32_temp - u8_temp;                   /* 4 - Updating the floating point number after printing the number before decimal point*/
		u8_temp  = (f32_temp * 10);                      /* 5 - Moving the decimal point to right to capture the next number to be printed       */
		f32_temp = (f32_temp *(10*1.0));                 /* 6 - Moving the decimal point to right and store the result as float to maintain      */
		                                                 /*     the remaining numbers after the decimal point to print them in order             */
														 /****************************************************************************************/
	} while (u8_digits);
}

void LCD_cursorMove(uint8_t u8_direction){
	if(LEFT == u8_direction){
		LCD_command(LEFT);
		TIMER0_msdelay(5);
	}
	else if(RIGHT == u8_direction){
		LCD_command(RIGHT);
		TIMER0_msdelay(5);
	}
}
