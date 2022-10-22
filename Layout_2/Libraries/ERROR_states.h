#ifndef ERROR_STATES_H_
#define ERROR_STATES_H_

enum errorCodes_t
{
	/* GPIO ERROR STATE */
	WRONG_PIN  = 0x01,
	WRONG_PORT = 0x02,
	WRONG_MODE = 0x03,
	NO_ERRORS  = 0x04,
	
	/* ADC ERROR STATE */
	WRONG_CHANNEL = 0x11,
	WRONG_VREF    = 0x12
};

#endif 