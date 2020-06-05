#include<lpc17xx.h>

#include "PLL.h"
#include "LCD.h"
#include "Timer.h"
#include "PWM.h"


//========================== Main Function =============================

int main()
{
	PLL_Init(100);
	PWM_Init(99);
	LPC_PINCON->PINSEL3=0x00228A20;
	PWM_Match(0,1000);
	PWM_Match(1,182);
	PWM_Match(2,348);
	PWM_Match(3,259);
	PWM_Match(4,653);
	PWM_Match(5,437);
	PWM_Match(6,919);
	PWM_Enable();
	while(1)
	{
	}
}

//======================================================================
