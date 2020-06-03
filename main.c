//====================================================================================//
//the pc should make a setup first by sending the room numbers through uart          //
//there are 5 rooms, so 5 room numbers should be send                               //
//the program will run after the setup                                             //
//the room number is send to the controller first that will get an option on it   //
//the option is send after choosing the room number                              //
// option 0 = check in                                                          //
// to check in the password is send through the uart (4 chars)                 //
//option 1 = check out                                                        //
//option 2 = room service                                                    //
//the room can be entered using the password that is entered at the check in//
//the password is enter using the keypad if the room status is occuped     //
//========================================================================//


#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "UART_driver.h"
#include "portF.h"
#include "keypad.h"
void check_options (char opt);
void solenoid_locked (void);
void solenoid_unlocked (void);  
void get_password(void);
_Bool password_checker(char pass[]);	
static char password[4];	//variable to save the password in it 
static char room_numbers[5]; //array to save the room numbers in it
static int room_status={0}; //array to store the room status in it 0= empty 1= occupied
//void SystemInit(){} 
int main(void){
	PortF_init();

	UART_init();
	PortC_init();
  PortD_init();
	

	for(int i =0 ; i <5 ;i++){
		room_numbers[i]=UART_receive();
		
		
	}
	
	//the room that we control its number is at index 0
	while(1){
		char option;
		char room_num; 
		
		 room_num = UART_receive();
		 
		
		if(room_num==room_numbers[0]){
		option = UART_receive(); // to get the option from the uart 
		check_options(option);}
		
		
		
	
		if(room_status==1){
			get_password();
		}
		
	
	}







}
void check_options (char opt)	//el mfrod el option hena yegi mn el uart
{
	 if (opt == '0') //check in 
	 {	room_status=1;
			int i;
		 	for ( i = 0 ; i < 4 ; i++)
			{
					password[i]=UART_receive(); //getting password from uart
				password[i]='1';
			}
			
			solenoid_locked ();	
			
				
	 }
	 
	 	else if (opt == '1') //check out
	 {	room_status=0;
			 solenoid_locked ();	
	 }
	 
	 
	  else if (opt =='2') //room service
	 {	
				solenoid_unlocked ();  
	 }
	 
	  
		else
		{
				solenoid_locked ();	
		}
	 
 }
 void solenoid_locked (void){
	 LED_OFF(); //if the solenoid locked the led will be off
 }
void solenoid_unlocked (void){
	LED_ON(); // if the solenoid unlocked the led will be on 
}  
void get_password(void){	
			int i;
		  char pa[4];
		 	for ( i = 0 ; i < 4 ; i++)
			{
					password[i]=(char)KeyPad_getPressedKey(); //getting password from the keypad
				
			}
			if(password_checker(pa)) {
					solenoid_unlocked ();  
			}
			
				else
				{
						solenoid_locked ();	
				}
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
