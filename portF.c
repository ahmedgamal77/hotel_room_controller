#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "portF.h"



void PortF_init(void){	
	SYSCTL_RCGCGPIO_R |= 0x00000020; //activate portf
	while( (SYSCTL_RCGCGPIO_R & 0x20)==0 ) ;   
	GPIO_PORTF_DIR_R = 0X0E ; //output pf1,pf2,pf3
	GPIO_PORTF_DEN_R = 0X0E;  //enable digital
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock portF
	GPIO_PORTF_DATA_R=0x00; //led off initially
		
}
void LED_ON(void){
	
	GPIO_PORTF_DATA_R=0x04;  
}

void LED_OFF(void){
	GPIO_PORTF_DATA_R=0x00; 
}