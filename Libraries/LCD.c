#include <lpc17xx.h>
#include "LCD.h"
#include "Timer.h"

//================================== LCD CONVERT =======================================
void LCD_Convert(unsigned char g)
 {
	 if(g&0x10) dset |=(1<<d4); else dclr|= (1<<d4);  
	 if(g&0x20) dset |=(1<<d5); else dclr|= (1<<d5);
	 if(g&0x40) dset |=(1<<d6); else dclr|= (1<<d6);
	 if(g&0x80) dset |=(1<<d7); else dclr|= (1<<d7);
	 
	 LPC_GPIO1->FIOSET |=(1<<EN);
	 Delay(10);
	 LPC_GPIO1->FIOCLR |=(1<<EN);

	 if(g&0x01) dset |=(1<<d4); else dclr|= (1<<d4);
	 if(g&0x02) dset |=(1<<d5); else dclr|= (1<<d5);
	 if(g&0x04) dset |=(1<<d6); else dclr|= (1<<d6);
	 if(g&0x08) dset |=(1<<d7); else dclr|= (1<<d7);
	 	 
	 LPC_GPIO1->FIOSET |=(1<<EN);
	 Delay(10);
	 LPC_GPIO1->FIOCLR |=(1<<EN);
 }
//=======================================================================================
//================================== LCD COMMAND ========================================
 void LCD_CMD(unsigned char c)
 {
   LPC_GPIO1->FIOCLR |=(1<<RS); 									// Clear RW and RS for sending command
	 LPC_GPIO1->FIOCLR |=(1<<RW);
   LCD_Convert(c);	 
 }
//=======================================================================================
//================================== LCD DELAY ==========================================
 void LCD_Delay(int Delay_Value)
 {
	int count;
  #define message_line_1a "Please wait for "
  #define message_line_1b "seconds"
	LCD_Display(1,message_line_1a);
	LCD_Display_Char_Position(0xC2,message_line_1b);
  for(count=0;count<Delay_Value;count++)
	 {
			 LCD_Display_Number_Position(0xC0,(Delay_Value-count));
			 Delay(1000);
	 }
 }
//=======================================================================================	
//================================== LCD INITALIZE ======================================
 void LCD_Init(void)
 {
	 LPC_PINCON->PINSEL3 &=~(0X3F<<22);  										// Setting GPIO for port 1 pins 22,23,24
	 LPC_PINCON->PINSEL4 &=~(0xF<<4);  										// Setting GPIO for port 2 pins 4,5,6,7
	 LPC_GPIO1->FIODIR|=(1<<RS)|(1<<RW)|(1<<EN);	  // Output for P1.22-24
	 LPC_GPIO2->FIODIR|=(0XF0); 										// Output for P2.4-7
	 Delay(10);
	 LCD_CMD(0x0E);																	// Clear LCD
	 Delay(10);
	 LCD_CMD(0x80); 																// 1st position of first line
	 Delay(10);
	 LCD_CMD(0x01); 																// Curson ON
	 Delay(10);
	 LCD_CMD(0x28); 																// 4 Bit mode 
	 Delay(10);
	 LCD_Clear(1);																	
	 Delay(10);
	 LCD_Clear(2);
 }
//=========================================================================================
//================================== LCD DATA =============================================
void LCD_DATA(unsigned char v)
 {
	 LPC_GPIO1->FIOSET |=(1<<RS); // RS=1,RW=0 for data transmission
	 LPC_GPIO1->FIOCLR |=(1<<RW);
	 LCD_Convert(v);
 }
//=========================================================================================
//================================== LCD CLEAR ============================================
void LCD_Clear(int line)
 {
	 int temp=0;
   if(line==1)	 																	// Place the cursor on correct line
			LCD_CMD(0x80); 
	 else if(line==2) 
			LCD_CMD(0xC0);
	 	   
	 Delay(1);
	 
	 while(temp<16)
	 {
	   Delay(1);
		 LCD_DATA(clear[temp]); 											// Clear the Line
		 temp++;
	 }
 }
//=========================================================================================
//================================== LCD DISPLAY ==========================================
void LCD_Display(int line,char a[])
 {
	 int temp;
	 
LCD_Clear(line);
	
		if (line==1) 																			// Place the curson on correct lines
			LCD_CMD(0x80);
		else if (line == 2)  
			LCD_CMD(0xC0);

	 temp=0;
	 while(a[temp]!='\0') 													// Till message is not null
	 {
  	 Delay(10);
		 LCD_DATA(a[temp]);
		 temp++; 																			// For next character in the message
	 }
 }
//=========================================================================================	
//================================== LCD DISPLAY NUMBER ===================================

 void LCD_Display_Num(int line,int x) 						// Display the number
 {
  int temp,v;
  temp=x;
	if (line==1) 
	{
		LCD_Clear(1);
		LCD_CMD(0x80);
	}
	else if (line == 2)  
	{
		LCD_Clear(2);
		LCD_CMD(0xC0);
	}
			
	if(x>=0 && x<10)
	{
			v=temp%10;
			LCD_DATA(v+0x30);
	}
	else if(x>=10 && x<100)
	{
			v=(temp/10);
			LCD_DATA(v+0x30);
			v=temp%10;
			LCD_DATA(v+0x30);
	}
	else if(x>=100 && x<1000)
	{
			v=(temp/100);
			LCD_DATA(v+0x30);
			v=((temp%100)/10);
			LCD_DATA(v+0x30);
			v=temp%10;
			LCD_DATA(v+0x30);
	}
	else if(x>=1000 && x<10000)
	{
			v=(temp/1000);
			LCD_DATA(v+0x30);
			v=((temp%1000)/100);
			LCD_DATA(v+0x30);
			v=((temp%100)/10);
			LCD_DATA(v+0x30);
			v=temp%10;
			LCD_DATA(v+0x30);
	}
	else if(x>=10000 && x<100000)
	{
			v=temp/10000;
			LCD_DATA(v+0x30);
			v=((temp%10000)/1000);
			LCD_DATA(v+0x30);
			v=((temp%1000)/100);
			LCD_DATA(v+0x30);
			v=((temp%100)/10);
			LCD_DATA(v+0x30);
			v=temp%10;
			LCD_DATA(v+0x30);
	}
	else if(x>=100000 && x<1000000)
	{
			v=temp/100000;
			LCD_DATA(v+0x30);
			v=((temp%100000)/10000);
			LCD_DATA(v+0x30);
			v=((temp%10000)/1000);
			LCD_DATA(v+0x30);
			v=((temp%1000)/100);
			LCD_DATA(v+0x30);
			v=((temp%100)/10);
			LCD_DATA(v+0x30);
			v=temp%10;
			LCD_DATA(v+0x30);
	
	}
	else
	{
		int temp,number[10],i=0;
		for(temp=x;temp>0;temp=temp/10)
			{
				number[i]=(temp%10);
				i++;
			}
		
		for(temp=(i-1);temp>=0;temp--)
			{
				while(((LPC_UART0->LSR)&0X20)==0x00);
				LCD_DATA((number[temp]+0x30));
			}
	}
}
//=========================================================================================	
//================================== LCD DISPLAY STRING - POSITION ========================

 void LCD_Display_Char_Position(unsigned char Position, unsigned char v[])
 {
	 int temp=0;
	 LCD_CMD(Position);
	 while(v[temp]!='\0') // Till message is not null
	 {
  	 Delay(10);
		 LCD_DATA(v[temp]);
		 temp++; // For next character in the message
	 }
 }

//=========================================================================================
//============================= LCD DISPLAY CHARACTER - POSITION ==========================
  void LCD_Display_Character_Position(unsigned char Position, unsigned char v)
 {
	 LCD_CMD(Position);
		 LCD_DATA(v);
 }

//=========================================================================================	
//================================ LCD DISPLAY NUMBER - POSITION ==========================
  void LCD_Display_Number_Position(unsigned char Position,int Number) // Displaying the number
 {
	 int temp,v;
	 temp=Number;

	LCD_CMD(Position);
		
if(Number>=0 && Number<10)
{
		v=temp%10;
		LCD_DATA(v+0x30);
}
else if(Number>=10 && Number<100)
{
		v=(temp/10);
		LCD_DATA(v+0x30);
		v=temp%10;
		LCD_DATA(v+0x30);
}
else if(Number>=100 && Number<1000)
{
		v=(temp/100);
		LCD_DATA(v+0x30);
		v=((temp%100)/10);
		LCD_DATA(v+0x30);
		v=temp%10;
		LCD_DATA(v+0x30);
}
else if(Number>=1000 && Number<10000)
{
		v=(temp/1000);
		LCD_DATA(v+0x30);
		v=((temp%1000)/100);
		LCD_DATA(v+0x30);
		v=((temp%100)/10);
		LCD_DATA(v+0x30);
		v=temp%10;
		LCD_DATA(v+0x30);
}
else if(Number>=10000 && Number<100000)
{
		v=temp/10000;
		LCD_DATA(v+0x30);
		v=((temp%10000)/1000);
		LCD_DATA(v+0x30);
		v=((temp%1000)/100);
		LCD_DATA(v+0x30);
		v=((temp%100)/10);
		LCD_DATA(v+0x30);
		v=temp%10;
		LCD_DATA(v+0x30);
}
}
//=========================================================================================	
//================================== LCD DISPLAY NUMBER -AAYUSHI ==========================

void LCD_display2(int a)
{
	int k,l;
	int h[4];
	for(k=0;k<4;k++)
	{
		h[k]=a%10;
		a=a/10;
	}
	for(l=0;l<4;l++)
	{
		LCD_DATA(h[3-l]+0x30);
		Delay(10);
	}
}
//=========================================================================================
