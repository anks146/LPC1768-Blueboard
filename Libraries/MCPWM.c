#include<lpc17xx.h>
#include "MCPWM.h"


void Match_MCPWM(int Register,int Value)
{
	if(Register==0)
		LPC_MCPWM->MCPW0=Value;
	else if(Register==1)
		LPC_MCPWM->MCPW1=Value;
	else if(Register==2)
		LPC_MCPWM->MCPW2=Value;
}

void Limit_MCPWM(int Register,int Value)
{	
	if(Register==0)
		LPC_MCPWM->MCPER0=Value;
	else if(Register==1)
		LPC_MCPWM->MCPER1=Value;
	else if(Register==2)
		LPC_MCPWM->MCPER2=Value;
}

void MCPWM_Init(void)
{
	LPC_SC->PCLKSEL1=0x00;
	LPC_SC->PCONP|=(1<<17);
	LPC_SC->PCLKSEL1|=0x42000200;
	LPC_MCPWM->MCCON_SET=(Passive_Timer);
	LPC_MCPWM->MCCON_CLR |=Edge_Aligned_Timer_MCPWM;
}

void MCPWM_Start(void)
{
	LPC_MCPWM->MCCON_SET|=Start_Timer_MCPWM;
}
