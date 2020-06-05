#include<lpc17xx.h>
#include "SPI.h"
#include "LCD.h"

void SPI_Init(void)
{
	LPC_SC->PCONP|=(1<<8);
	LPC_SC->PCLKSEL0&=~(3<<16);
	LPC_SC->PCLKSEL0|=(1<<16);
	//LPC_SC->PCLKSEL0=0x00000004;
	LPC_SPI->SPCR= (1<<2)|(1<<11); // SPI controller sends and receive number of bits/transfer set by bit[11:8]
	LPC_PINCON->PINSEL0=0xC0000000;//	set p0.15 as clock of spi
	LPC_PINCON->PINSEL1&=~((3<<0)|(3<<2)|(3<<4));// p0.16-slave select,p0.17-MISO,p0.18-MOSI
	LPC_PINCON->PINSEL1|=(3<<0)|(3<<2)|(3<<4);
	//LPC_PINCON->PINSEL1|=0x00000002;
//	LPC_GPIO0->FIOSET|=(1<<16);
	return;
}

uint8_t Data_Transfer(void)
{
	while((LPC_SPI->SPSR&0x80)==0x00);
	return 1;
}

void Send_Data(char c)
{
	LPC_SPI->SPDR=c;
	return;
}

char Receive_Data(void)
{
	return LPC_SPI->SPDR;
}

void Send_SPI(char *c)
{
	int i=0;
	while(c[i]!='\0')
	{
		Data_Transfer();
		Send_Data(c[i]);
		i++;
	}
	return;
}

int Receive_SPI(int num)
{
	int * Rec_Add;
	char Dat[7];
	int k=0;
	LCD_Display(1,"Receive SPI");
	while(k<num)
	{
		Data_Transfer();
		Dat[k]=Receive_Data();
		k++;
	}
	Rec_Add=(int *)&Dat[0];
	LCD_Display_Num(1,(int)Rec_Add);
	LCD_Display(2,"Return to main");
	return (int)Rec_Add;
}
