#include<lpc17xx.h>
#include "UART.h"
#include "PLL.h"

//================================== UART INITIALIZE========================

void UART_Initialize(int baud)
{
	
	LPC_SC->PCONP|=(1<<3);  // Power ON for UART0
  LPC_PINCON->PINSEL0|=0X50; // Configuring pins for UART
	//LPC_SC->PCLKSEL0|=(1<<6); // PCLK=CCLK
	LPC_SC->PCLKSEL0&= ~(3<<6); // PCLK=CCLK/4 for UART
	LPC_UART0->FCR=0X07; // Reset and Enable Rx and Tx FIFO
	LPC_UART0->TER=0X80; // Start of transmission
	LPC_UART0->IER|=0X01; // Enable interrupt for receiving data
	LPC_UART0->LCR=0X83; // Enable Divisor Latch for loading DLL and DLM

	
	if (baud==2400)
	{
	LPC_UART0->FDR=0XA1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x47; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==4800)
	{
	LPC_UART0->FDR=0X91; // Load Fractional Divider Value
	LPC_UART0->DLL=0x23; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==7200)
	{
	LPC_UART0->FDR=0XF2; // Load Fractional Divider Value
	LPC_UART0->DLL=0x17; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==9600)
	{
	LPC_UART0->FDR=0XC1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x12; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==14400)
	{
	LPC_UART0->FDR=0XC1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x0C; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==19200)
	{
	LPC_UART0->FDR=0XC1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x09; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==28800)
	{
	LPC_UART0->FDR=0XC1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x06; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==38400)
	{
	LPC_UART0->FDR=0X92; // Load Fractional Divider Value
	LPC_UART0->DLL=0x04; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if (baud==57600)
	{
	LPC_UART0->FDR=0XC1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x03; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	}
	else if(baud==115200)
	{
	LPC_UART0->DLL=0x36;
	LPC_UART0->DLM=0;
	}
	LPC_UART0->LCR=0X03; // Disable Divisor Latch 
}
//========================================================================	
//========================== UART TRANSMIT CHARACTER =====================
void UART0_TxChar(char ch)
{
	while(((LPC_UART0->LSR)&0X20)==0x00); // Wait till THR empty
	LPC_UART0->THR=ch; // Transmit character
}
//========================================================================	
//=========================== UART TRANSMIT NUMBER =======================	
void UART0_TxNum(int num)
{
	  if(num>=0 && num<10)
		{
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num%10)+0x30);
		}
		else if(num>=10 && num<100)
		{
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num/10)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num%10)+0x30);
		}
		else if(num>=100 && num<1000)
		{
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num/100)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=(((num%100)/10)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num%10)+0x30);
		}
		else if(num>=1000 && num<10000)
		{
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num/1000)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=(((num%1000)/100)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=(((num%100)/10)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num%10)+0x30);
		}
		else if(num>=10000 && num<100000)
		{
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num/10000)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=(((num%10000)/1000)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=(((num%1000)/100)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=(((num%100)/10)+0x30);
		while(((LPC_UART0->LSR)&0X20)==0x00);
		LPC_UART0->THR=((num%10)+0x30);
		}
		else
		UART0_SendString("INVALID NUMBER");
}
//==================================================================	
//========================= UART SEND STRING========================
void UART0_SendString(char *ch)
{
	int i=0;
	while(ch[i]!='\0')
	{
  UART0_TxChar(ch[i]); // Transmit the character
		i++;
	}
}
//==================================================================
