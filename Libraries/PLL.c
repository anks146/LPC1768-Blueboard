#include <lpc17xx.h>
#include "PLL.h"

//===================================== PLL FEED =========================================
void PLL_Feed()
{
LPC_SC->PLL0FEED=0XAA;                    // Feed sequence for loading values to CONTROL and CONFIG registers
LPC_SC->PLL0FEED=0X55;
}
//========================================================================================
//===================================== PLL INITIALIZE ===================================
void PLL_Init(int freq)
{
	int m,n,d;
  	LPC_SC->SCS=0X20;
	while ((LPC_SC->SCS & (1<<6)) == 0);		// Wait for oscillator to be ready  
	LPC_SC->PLL0CON=0X01;		                // DISCONNECT PLL0
	PLL_Feed();
	LPC_SC->PLL0CON = 0X00;		              // DISABLE PLL0
	PLL_Feed();
	LPC_SC->CLKSRCSEL=0X01;                 // Select Local oscillator as clock source for PLL0
	LPC_SC->CCLKCFG=0X00;		                // Clear value of Clock Divider
	LPC_SC->PLL0CFG=0x00;	                  // Clear the present configuration
	PLL_Feed();

	if(freq==12)
	{
	m=0x16;
	n=0x01;
	d=0x16;
	}

	else if(freq==3)
	{
	m=0x16;
	n=0x01;
	d=0x5B;
	}

	else if(freq==6)
	{
	m=0x16;
	n=0x01;
	d=0x2D;
	}

	else if(freq==10)
	{
	m=0x18;
	n=0x01;
	d=0x1D;
	}

	else if(freq==25)
	{
	m=0x18;
	n=0x01;
	d=0x0B;
	}

	else if(freq==50)
	{
	m=0x18;
	n=0x01;
	d=0x05;
	}

	else if(freq==75)
	{
	m=0x18;
	n=0x01;
	d=0x03;
	}
	
	else if(freq==92)
	{
	m=0x11F;
	n=0x18;
	d=0x02;
	}
	
	else if(freq==96)
	{
	m=23;
	n=1;
	d=2;
	}
  
	else if(freq==100)
	{
	m=0x18;
	n=0x01;
	d=0x02;
	}
	
	LPC_SC->PLL0CFG|=((m)|(n<<16));   			// Load new configuration values of Multiplier and Divider to configure current controlled Frequency Fcco
	PLL_Feed();
	LPC_SC->PLL0CON=0X01;                   		// Enable PLL
	PLL_Feed();
	LPC_SC->CCLKCFG=d;                   			// Load values of new clock divider
	
	while(((LPC_SC->PLL0STAT>>26)&0X01)==0);// Wait till PLL Lock to applied Peripheral clock 
	LPC_SC->PLL0CON=0x03;                   // Connect PLL with PCLK
	PLL_Feed();
	return;
	}
//========================================================================================
