#include "stdint.h"
#include "D:/keil/EE319KwareSpring2020/inc/TM4C123GH6PM.h"
#include "UART_driver.h"
#include "portF.h"
void check_options (char opt);
void solenoid_locked (void);
void solenoid_unlocked (void);  
_Bool password_checker(char pass[]);	
void SystemInit(){} 
int main(void){
	PortF_init();
	UART_init();
	while(1){
		char option;
		// option = UART_receive() // to get the option from the uart 
		option = '0';
		check_options(option);
		option = '3';
		check_options(option);
		
		option='1';
		check_options(option);
		option = '0';
		check_options(option);
		option = '2';
		check_options(option);
		
		
		
		
	}







}
void check_options (char opt)	//el mfrod el option hena yegi mn el uart
{
	 if (opt == '0') //check in 
	 {		
			int i;
		 	for ( i = 0 ; i < 4 ; i++)
			{
					//password[i]=UART_receive(); //getting password from uart
				password[i]='1';
			}
				
	 }
	 
	 	else if (opt == '1') //check out
	 {	
			 solenoid_locked ();	
	 }
	 
	 
	  else if (opt =='2') //room service
	 {	
				solenoid_unlocked ();  
	 }
	 
	  else if (opt == '3') //enter the room
	 {	
		 
		 	int i;
		  char pa[4];
		 	for ( i = 0 ; i < 4 ; i++)
			{
					//password[i]=UART_receive(); //getting password from uart
				pa[i]='1';
			}
			if(password_checker(pa)) {
					solenoid_unlocked ();  
			}
			
				else
				{
						solenoid_locked ();	
				}
	 }
 }
 void solenoid_locked (void){
	 LED_OFF(); //if the solenoid locked the led will be off
 }
void solenoid_unlocked (void){
	LED_ON(); // if the solenoid unlocked the led will be on 
}  
_Bool password_checker(char pass[]){
int i;
		for ( i = 0 ; i < 4 ; i++)
		{
			if (password[i]!= pass[i])
				return 0;
		}
		
		return 1;
}	
