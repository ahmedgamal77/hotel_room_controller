#include "stdint.h"
#include "keypad.h"
#include "std_types.h"

// FUNCTION_2
#if (N_col == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint32_t KeyPad_4x4_adjustKeyNumber(uint32_t button_number);
#endif

// FUNCTION_3
uint16 KeyPad_getPressedKey(void)
{
	uint16 col,row;
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			/* 
			 * each time only one of the column pins will be output and 
			 * the rest will be input pins include the row pins 
			 */ 
			KeyPad_ROWS_DIR =0x00000000; //ROWS ON PORT D
			KeyPad_COLUMNS_DIR = 0x10<<col; //col on port c
			
			/* 
			 * clear the output pin column in this trace and enable the internal 
			 * pull up resistors for the rows pins
			 */ 
			Keypad_ROWS_DATA  =0xFFFFFFFF;
			Keypad_COLUMNS_DATA = (~(0x10<<col));

			for(row=0;row<N_row;row++) /* loop for rows */
			{
				if(BIT_IS_CLEAR(Keypad_ROWS_DATA,row)) /* if the switch is press in this row */ 
				{
					#if (N_col == 4)
						return KeyPad_4x4_adjustKeyNumber((row*N_col)+col+1);
					#endif
				}
			}
		}
	}	
}
void PortC_init(void)
{	
	SYSCTL_RCGCGPIO_R |= 0x00000004; //portC activated
	while( (SYSCTL_RCGCGPIO_R & 0x04)==0 ) ;   
	GPIO_PORTC_DIR_R = 0X00; //input 
	GPIO_PORTC_DEN_R = 0XFF;  //enable digital
	GPIO_PORTC_DATA_R=0x00; 
		
}

void PortD_init(void)
{	
	SYSCTL_RCGCGPIO_R |= 0x00000008; //portD activated
	while( (SYSCTL_RCGCGPIO_R & 0x08)==0 ) ; 
	GPIO_PORTD_DIR_R = 0X00 ; //input 
	GPIO_PORTD_DEN_R = 0XFF;  //enable digital
	GPIO_PORTD_DATA_R=0x00; 
		
}
//Function_2_Defention 
#if (N_col == 4)
 
static uint32_t KeyPad_4x4_adjustKeyNumber(uint32_t button_number)
{
	switch(button_number)
	{
		case 1:
			     return 7;
           break;
		case 2: 
			     return 8; 
				   break;
		case 3: 
			     return 9; 
				   break;
		case 4: 
			     return '%'; // ASCII Code of %
				   break;
		case 5: 
			     return 4; 
				   break;
		case 6: 
			     return 5;
				   break;
		case 7:
     			 return 6; 
				   break;
		case 8: 
			     return '*'; /* ASCII Code of '*' */
				   break;		
		case 9: 
			     return 1; 
				   break;
		case 10: 
			     return 2; 
				   break;
		case 11: 
			     return 3; 
				   break;
		case 12: 
			     return '-'; /* ASCII Code of '-' */
				   break;
		case 13: 
			     return 13;  /* ASCII of Enter */
				   break;			
		case 14: 
			     return 0; 
				   break;
		case 15: 
			     return '='; /* ASCII Code of '=' */
				   break;
		case 16:
     			return '+'; /* ASCII Code of '+' */
				  break;
		default: return button_number;								 						
	}
} 

#endif
