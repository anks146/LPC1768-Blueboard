#include<lpc17xx.h>

#include "PLL.h"
#include "MCPWM.h"


//========================== Main Function =============================

int main()
{
	PLL_Init(100);
	LPC_PINCON->PINSEL3=0x05141040;
	
	Limit_MCPWM(0,10000);
	Limit_MCPWM(1,7500);
	Limit_MCPWM(2,1000);
	
	Match_MCPWM(0,2000);
	Match_MCPWM(1,5500);
	Match_MCPWM(2,610);
	
	MCPWM_Init();
	MCPWM_Start();
	while(1)
	{
		//
	}
}
//======================================================================
