#include <lpc17xx.h>

#include "Timer.h"
#include "UART_Post.h"
#include "LCD.h"
#include "Buzzer.h"

//================================== UART0 TRANSMIT CHAR =============================
void UART0_TxChar(char ch)
{
	while(((LPC_UART0->LSR)&0X20)==0x00);
	LPC_UART0->THR=ch;
}

//====================================================================================	
//================================== UART0 SEND STRING ===============================
void UART0_SendString(char *ch)
{
	int count=0;
	while(ch[count]!='\0')
	{
  UART0_TxChar(ch[count]);
		count++;
	}
}

//====================================================================================
//================================== UART0 TRANSMIT NUMBER============================
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
		{
			int temp,number[10],i=0;
			for(temp=num;temp>0;temp=temp/10)
			{
				number[i]=(temp%10);
				i++;
			}
			for(temp=(i-1);temp>=0;temp--)
			{
				while(((LPC_UART0->LSR)&0X20)==0x00);
				LPC_UART0->THR=(number[temp]+0x30);
			}
		}
}
//===================================================================================	
//===================================== UART INIT ===================================

void UART_Init(void)
{
	LPC_SC->PCONP|=(1<<3);  // Power ON for UART0
  LPC_PINCON->PINSEL0|=0X50; // Configuring pins for UART
	//LPC_SC->PCLKSEL0|=(1<<6); // PCLK=CCLK
	LPC_SC->PCLKSEL0&= ~(3<<6); // PCLK=CCLK/4 for UART
	LPC_UART0->FCR=0X07; // Reset and Enable Rx and Tx FIFO
	LPC_UART0->TER=0X80; // Start of transmission
	LPC_UART0->LCR=0X83; // Enable Divisor Latch for loading DLL and DLM
	LPC_UART0->FDR=0XC1; // Load Fractional Divider Value
	LPC_UART0->DLL=0x12; // Load DLL Value
	LPC_UART0->DLM=0X00; // Load DLM Value
	LPC_UART0->LCR=0X03; // Disable Divisor Latch
	Delay(10);
}

//===================================================================================	
//===================================== UART POST ===================================

void UART0_POST(void)
{
	char Sent[]= ("ANKIT");
	int count=0,Check=0;
	char Recieved[5];
	UART_Init();
	LCD_Display(1,"Test Start");
	while(count<5)
	{
	while((LPC_UART0->LSR & 0X20) == 0X01);
		LPC_UART0->THR=Sent[count];
	while((LPC_UART0->LSR &	0x01) == 0x00);
		Recieved[count]=LPC_UART0->RBR;
	
	if(Recieved[count]==Sent[count])
		Check++;

	count++;
	}
	
	LCD_Display(1,Recieved);
	LCD_Display_Num(2,count);
	Delay(2000);
	if(Check==6)
		LCD_Display(2,"UART OK");
	else
	{
		LCD_Display(2,"UART NOT OK");
		Buzzer_Sound(4);
	}
}
//===================================================================================
