#include <lpc17xx.h>

#include "PLL.h"
#include "Timer.h"
#include "LCD.h"
#include "SPI.h"

// Private defines 

#define Delay_Value 200
#define PreScalar_Value 99999
#define CCLK_Value 100
#define Match_Register 0
#define Char_Num 9

//================================ MAIN FUNCTION ======================================
int main()
{
	int loop=0;
	int Rec_Cnt=0;
////	char *c;
	char dummy;
	char Rec_Dat[Char_Num];
//	int m=0;
	PLL_Init(CCLK_Value);                        // Initialize the PLL for CPU Clock Frequency
	Timer_Init(PreScalar_Value);                 // Initialize the timer with pre-defined pre-scalar values
	LCD_Init();
	SPI_Init();
	LCD_Display(1,"Ready to receeive");
	Delay(Delay_Value);
//	LPC_GPIO0->FIOCLR|=(1<<16);
//	LPC_PINCON->PINSEL0&=~((3<<30U));
//	LPC_GPIO0->FIOCLR|=(1<<16);
	LCD_Display(1,"Receiving now");
	while(	(	(LPC_GPIO0->FIOPIN)&(1<<16))==(1<<16));
	Data_Transfer();
	dummy=LPC_SPI->SPDR;
	while(1)
		{
			// =========================================== Receive Data ================================================
//				while(	(	(LPC_GPIO0->FIOPIN)&(1<<16))==(1<<16));
			//LCD_Display(1,"Receiving Data");//while((&c)!='\0' & m<13)
				Rec_Cnt=0;
				while((LPC_SPI->SPSR&0x80)==0x80); // While data transfer complete
				while(Rec_Cnt<10)
				{
					Data_Transfer();
//						if(Rec_Cnt==0)
//							dummy=LPC_SPI->SPDR;
//						else
							Rec_Dat[Rec_Cnt]=LPC_SPI->SPDR;
					Rec_Cnt++;
				}
				//LCD_Display(1,"Data Received:");
				LCD_Display(2,Rec_Dat);
//				while((LPC_SPI->SPSR&0x80)==0x80); // While data transfer complete
//		Delay(1000);
//		
// ================================================== Receive End ================================================
			//LCD_Display(1,"Transmit now");
			  Send_SPI("HELLO STM!");
//			LCD_Display(1,"Data Sent");
//			LCD_Display_Num(2,loop);
//			loop++;
//	Delay(10);
		}
}
//================================ END OF MAIN FUNCTION ===============================
