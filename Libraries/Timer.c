#include <lpc17xx.h>
#include "Timer.h"
#include "Waveform.h"

//=============================== START TIMER ===============================

void Start_Timer(void)
{
	LPC_TIM0->TCR=0X01;
}
//===========================================================================
//================================ STOP TIMER ===============================
void Stop_Timer(void)
{
	LPC_TIM0->TCR=0X00;
}
//===========================================================================
//================================ RESET TIMER ==============================
void Reset_Timer(void)
{
	LPC_TIM0->TCR=0X02;
}
//===========================================================================
//=============================== TIMER INIT ================================
void Timer_Init(int Prescalar)
{
  LPC_SC->PCONP |=(1<<1);               // Supply Power to Timer 0
	//LPC_SC->PCLKSEL0&= ~(0X03<<2);      // TCLK=PCLK/4
	LPC_SC->PCLKSEL0|= (1<<2);            // TCLK=PCLK
	LPC_TIM0->CTCR=0X0;                   // Set Timer in Timer mode
	LPC_TIM0->PR=Prescalar;               // Setting Prescalar Register value
  Reset_Timer();                        // Timer Reset
}
//===========================================================================
//================================ DELAY ====================================
void Delay(int t)
{
	Reset_Timer();	
	Start_Timer();												
	while(LPC_TIM0->TC < t);							// Till counter < Time specified
	Stop_Timer();
}
//===========================================================================
//================================ TIMER INTERRUPT ==========================
void Timer_Interrupt(int mr, int Value)
{
	if(mr==0)
	{
		LPC_TIM0->MCR |=(1<<0)|(1<<1);      // Reset TC and enable interrupt when TC=MR0
		LPC_TIM0->MR0=Value;                // Set MR0 value
	}
	
	else if(mr==1)
	{
		LPC_TIM0->MCR |=(1<<3)|(1<<4);      // Reset TC and enable interrupt when TC=MR1
		LPC_TIM0->MR1=Value;                // Set MR1 value
	}
	
	else if(mr==2)
	{
		LPC_TIM0->MCR |=(1<<6)|(1<<7);      // Reset TC and enable interrupt when TC=MR2
		LPC_TIM0->MR2=Value;                // Set MR2 value
	}
	
	else if(mr==3)
	{
		LPC_TIM0->MCR |=(1<<9)|(1<<10);     // Reset TC and enable interrupt when TC=MR3
		LPC_TIM0->MR3=Value;                // Set MR3 value
	}
	
	NVIC_EnableIRQ(TIMER0_IRQn);          // Enable interrupt for Timer 0
}
//===========================================================================
//================================ TIMER INTERRUPT ==========================
void Timer_Interrupt_Reset(int mr)
{
	if(mr==0)
	{
		LPC_TIM0->MCR &=~((1<<0)|(1<<1));      // Disable interrupt for MR0
		LPC_TIM0->MR0=0;
	}
	
	else if(mr==1)
	{
		LPC_TIM0->MCR &=~((1<<3)|(1<<4));      // Disable interrupt for MR1
		LPC_TIM0->MR1=0;
	}
	
	else if(mr==2)
	{
		LPC_TIM0->MCR &=~((1<<6)|(1<<7));     // Disable interrupt for MR2
		LPC_TIM0->MR2=0;
	}
	
	else if(mr==3)
	{
		LPC_TIM0->MCR &=~((1<<9)|(1<<10));     // Disable interrupt for MR3
		LPC_TIM0->MR3=0;
	}
}
//===========================================================================
