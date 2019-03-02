#include "msp.h"
#include <stdint.h>
#include "BSP.h"

extern uint16_t PWMCycles;
extern uint32_t SubsystemFrequency;
uint16_t x, y = 0;
uint8_t select = 0;

void ChangeFreq(int freq, uint16_t duty){
	BSP_Buzzer_Set(freq, duty);

}

void FindLoc(void){
	if(x<341){
		if(y<341){
			ChangeFreq(1480,(uint16_t)256);
		}else if(y< 682){
			ChangeFreq(1175,(uint16_t)256);
		}else if(y<=1023){
			ChangeFreq(880,(uint16_t)256);
		}

	}else if(x<682){
		if(y<341){
			ChangeFreq(1661,(uint16_t)256);

		}else if(y< 682){
			ChangeFreq(880,(uint16_t)512);

		}else if(y<=1023){
			ChangeFreq(988,(uint16_t)256);
		}

	}else if(x <= 1023){
		if(y<341){
			ChangeFreq(1760,(uint16_t)256);

		}else if(y< 682){
			ChangeFreq(1319,(uint16_t)256);
		}else if(y<=1023){
			ChangeFreq(1109,(uint16_t)256);
			
		}
	}
}

int main(){
	WDT_A->CTL = WDT_A_CTL_PW|WDT_A_CTL_HOLD;
	BSP_Buzzer_Init((uint16_t) 0x00);
	BSP_Joystick_Init();
	BSP_Buzzer_Set(2048, (uint16_t)0);
	while(1){
		BSP_Joystick_Input(&x, &y, &select);
		FindLoc();
	}
}
