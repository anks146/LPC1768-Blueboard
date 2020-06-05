#include<lpc17xx.h>
#include "Timer.h"
#include "PLL.h"
#include "LCD.h"
#include "UART_AutoBaud.h"

#define DELAY_VALUE 900
#define PRESCALAR_VALUE 99999
#define CCLK_VALUE 100 // In MHz

//======================= GLOBAL VARIABLES ================================================
int Reciever_Counter=0;
char Recieved_Data[Size];
//=========================================================================================
//================================ UART INTERRUPT HANDLER =================================
void UART0_IRQHandler(void)
{
	char IIRval;
	IIRval=LPC_UART0->IIR;																	// For identifing the source of interrupt
	
	if(((IIRval>>1)&0x07) == 0x02) 													// If receved data is available
	{
			Recieved_Data[Reciever_Counter]=LPC_UART0->RBR;			// Store the received data and resetting the interrupt flag
			Reciever_Counter++;																	// Increment Receiver Counter

			if(Reciever_Counter==Size)
					Reciever_Counter=0;															// If max value reached, increment receiver counter
			
	}
	else if( ((IIRval>>8)&0x01)==0x01) 											// If Auto baud successful
		LPC_UART0->ACR|=(1<<8);																// Clear  Interrupt
		
		else if( ((IIRval>>9)&0x01)==0x01) 										// If Auto baud Timeout
		LPC_UART0->ACR|=(1<<9);	          										// Clear interrupt
}
//=========================================================================================
//===================================== MAIN FUNCTIONS ====================================
int main()
{
	int Loop_Count=0,count;
  char Clear_Array[1]=" ";
	char mes1[]=("Received Data");
	char mes2[]=("Data Recieved ");
	char no_data[]=("No data");
  PLL_Init(CCLK_VALUE); 																	// Initialize the PLL for CPU Clock Frequency
	Timer_Init(PRESCALAR_VALUE);														// Initialize the timer with pre-defined pre-scalar values
	LCD_Init();
 	UART_Initialize(); 																			// Initialize UART for AutoBaud
	Reciever_Counter=0;																			// Reset receiver counter
	NVIC_EnableIRQ(UART0_IRQn); 														// Enable UART0 interrupt
	Delay(1);
	UART0_SendString("Hi Ankit\r\n");
	Delay(1);
	LCD_Display(1,mes1);
	while(1)
	{
		if((Loop_Count%10)==0 && Loop_Count!=0 ) 							// Check for recieved data on every 10th Transmission
		{
			 if(Reciever_Counter>0)															// When data is received
				 {
						UART0_SendString("Recieved Data:  ");
						LCD_Display(2,mes2); 
					  for(count=0;count<Reciever_Counter;count++)
						{
							UART0_TxChar(Recieved_Data[count]); 				// Transmit recieved data on UART
							Recieved_Data[count]=Clear_Array[0]; 				// Delete the recieved data for next set of data
						}

							Reciever_Counter=0;
							UART0_SendString("\r\n");
				 }
			 else																								// When no data received
				 { 
					 UART0_SendString("No data recieved \r\n");
					 LCD_Display(2,no_data);
				 }
		}
				UART0_SendString("TRANSMISSION  ");
				UART0_TxNum(Loop_Count);
				UART0_SendString(" \r\n");		
				Loop_Count++;																			// Incrementing the Loop count for next transmission
				Delay(DELAY_VALUE);
	}	
}
//================================ END OF MAIN FUNCTION ===================================
