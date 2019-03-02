//#include "msp.h"
//#include <stdint.h>
//#include "BSP.h"

//extern uint16_t PWMCycles;
//static uint16_t x = 0; 
//static uint16_t y = 0;
//static uint8_t select = 0;

//int main(){
//	WDT_A->CTL = WDT_A_CTL_PW|WDT_A_CTL_HOLD;
//	
//	BSP_Buzzer_Init((uint16_t) 0x00);
//	BSP_Buzzer_Set((uint16_t) 0x200);
//	BSP_Joystick_Input(&x, &y, &select);
//	
//	PWMCycles = 1;
//	
//	//if (x < 341)
//	//{
//	//}
//	//else if (x)
//	
//}

#include "msp.h"
#include <stdint.h>
#include "BSP.h"

uint16_t PWMCycles;
uint32_t SubsystemFrequency = 3000000;
uint16_t x, y = 0;
uint8_t select = 0;

void changeFreq(int freq, uint16_t duty){
	PWMCycles = SubsystemFrequency/freq;
  	TA0CCR4 = (duty*PWMCycles)>>10;  // defines when output signal is cleared
  	TA0CCR0 = PWMCycles - 1;         // defines when output signals are set
	BSP_Buzzer_Set(duty);
}

void FindLoc(void){
	if(x<341){
		if(y<341){
			changeFreq(1480,(uint16_t)512);
		}else if(y< 682){
			changeFreq(1175,(uint16_t)512);
		}else if(y<=1023){
			changeFreq(880,(uint16_t)512);
		}

	}else if(x<682){
		if(y<341){
			changeFreq(1661,(uint16_t)512);

		}else if(y< 682){
			changeFreq(880,(uint16_t)0);

		}else if(y<=1023){
			changeFreq(988,(uint16_t)512);
		}

	}else if(x <= 1023){
		if(y<341){
			changeFreq(1760,(uint16_t)512);

		}else if(y< 682){
			changeFreq(1319,(uint16_t)512);
		}else if(y<=1023){
			changeFreq(1109,(uint16_t)512);
			
		}
	}
}



int main(){
	//PWMCycles = 0;
	//SubsystemFrequency = 0;
	
	WDT_A->CTL = WDT_A_CTL_PW|WDT_A_CTL_HOLD;
	BSP_Buzzer_Init((uint16_t) 0x00);
	BSP_Joystick_Init();
	BSP_Buzzer_Set((uint16_t)0);
	while(1){
		BSP_Joystick_Input(&x, &y, &select);
		FindLoc();
	}
}
