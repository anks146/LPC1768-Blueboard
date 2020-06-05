#include<lpc17xx.h>
#include "PWM.h"

//========================== PWM Initialize ===========================

void PWM_Init(int PreScalar)
{
	LPC_SC->PCONP|=(1<<5);					// Turn the power on
	LPC_SC->PCLKSEL0&=~(3<<12);			// Reset the clock
	LPC_SC->PCLKSEL0|=(1<<12); 			// For PCLK=CCLK
	LPC_PINCON->PINSEL3 &= ~(3<<26);
	LPC_GPIO1->FIODIR|=(1<<29);
	LPC_PWM1->PR=PreScalar;
	LPC_PWM1->MCR=(ResetEnableCH0)|InterruptEnableCH3;
	LPC_PWM1->PCR=(0X3F<<9);
}

//======================================================================
//========================== PWM Reset =================================

void PWM_Reset(void)
{
	LPC_PWM1->TCR|=	(1<<1);
	LPC_PWM1->TCR&=	~(1<<1);
}
//======================================================================
//========================== PWM Interrupt =============================

void PWM1_IRQHandler(void)
{
	int val;
	val=LPC_PWM1->IR;
	if((val&InterruptFlagCH3)==InterruptFlagCH3)
	{
		if(((LPC_GPIO1->FIOSET>>29)&0x01)==0x01)
			LPC_GPIO1->FIOCLR	|=(1<<29);
		else
			LPC_GPIO1->FIOSET |=(1<<29);
	}
		
	LPC_PWM1->IR|=InterruptFlagCH3;
}
//======================================================================
//========================== PWM Enable ================================

void PWM_Enable(void)
{
	LPC_PWM1->TCR|=	(1<<3)|(1<<0);
}

//======================================================================
//========================== PWM Match =================================

void PWM_Match(int Register,int Value)
{
	if(Register==0)
		LPC_PWM1->MR0=Value;
	else if(Register==1)
		LPC_PWM1->MR1=Value;
	else if(Register==2)
		LPC_PWM1->MR2=Value;
	else if(Register==3)
		LPC_PWM1->MR3=Value;
	else if(Register==4)
		LPC_PWM1->MR4=Value;
	else if(Register==5)
		LPC_PWM1->MR5=Value;
	else if(Register==6)
		LPC_PWM1->MR6=Value;
	
	return;
}

//======================================================================
