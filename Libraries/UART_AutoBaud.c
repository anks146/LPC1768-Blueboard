#include<lpc17xx.h>
#include<math.h>

#include "Timer.h"
#include "UART_AutoBaud.h"

//================================== UART INITALIZE ==================================
void UART_Initialize(void)
{
	LPC_SC->PCONP|=(1<<3);
  LPC_PINCON->PINSEL0|=0X50;
	LPC_SC->PCLKSEL0=(0X44); // PCLK=CCLK for UART & TIMER
	//LPC_SC->PCLKSEL0&= ~(3<<6); // PCLK=CCLK/4 for UART
	LPC_UART0->IER|=(0X01); 
	LPC_UART0->FCR=0X07;
	LPC_UART0->LCR=0X03;	
	LPC_UART0->ACR=0X07;
	while((LPC_UART0->ACR&0X01)==0X01); // Wait till Auto Baud Stops
	LPC_UART0->TER=0X80;
	//Delay(900);
}
//====================================================================================	
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

//void UART0_HEX(char ch)
//{
//	if(ch>=0 & ch<=9)
//		UART0_TxNum((int)ch);
//	else
//		UART0_TxChar(ch+(0x41-0x0A));
//}
