#include<lpc17xx.h>
#include "Timer.h"
#include "UART.h"
#include "PLL.h"
#include "LCD.h"

#define DELAY_VALUE 900
#define PRESCALAR_VALUE 99999
#define CCLK_VALUE 100 // In MHz
#define BAUD_RATE 115200

//============================ GLOBAL VARIABLES ================================
int Reciver_Counter=0;
char Recieved_Data[Size];
//==============================================================================

//============================= UART INTERRUPT HANDLER =========================
void UART0_IRQHandler(void)
{
	char IIRval;
	IIRval=LPC_UART0->IIR;																		// For identifing the source of interrupt
		
	if(((IIRval>>1)&0x07) == 0x02) 													// If receved data is available
	{
			Recieved_Data[Reciver_Counter]=LPC_UART0->RBR;			// Store the received data and resetting the interrupt flag
			Reciver_Counter++;																	// Increment the total number of received character

			if(Reciver_Counter==Size)														// If Array is full and the next character recieved will be outside the range of the Array Size
					Reciver_Counter=0;															// Reset receiver counter
	}
	
	else if( ((IIRval>>8)&0x01)==0x01) 											// If Auto baud successful
		LPC_UART0->ACR|=(1<<8);						// Clear  Interrupt
		
	else if( ((IIRval>>9)&0x01)==0x01) // If Auto baud Timeout
		LPC_UART0->ACR|=(1<<9);	          // Clear interrupt

}
//==============================================================================

//================================ MAIN FUNCTION ===============================
int main()
{
	int Loop_Count=0,count;
  char Clear_Array[1]=" ";
	char mes1[]=("Received Data");
	char mes2[]=("Data Recieved ");
	char no_data[]=("No data");
  PLL_Init(CCLK_VALUE); 																		// Initialize the PLL for CPU Clock Frequency
	Timer_Init(PRESCALAR_VALUE); 															// Initialize the timer with pre-defined pre-scalar values
	LCD_Init();																								// Initialize the LCD
 	UART_Initialize(BAUD_RATE); 															// Initialize UART for specific baud rate
	NVIC_EnableIRQ(UART0_IRQn); 															// Enable UART0 interrupt
	Delay(1);
	UART0_SendString("Hi Ankit\r\n");
	Delay(1);
	LCD_Display(1,mes1);
	while(1)
	{
		if((Loop_Count%10)==0 && Loop_Count!=0 ) 								// Checking for recieved data on every 10th Transmission
		{
			 if(Reciver_Counter>0) 																// When Data recieved
				 {
						UART0_SendString("Recieved Data:  ");
						LCD_Display(2,mes2); 
					  for(count=0;count<Reciver_Counter;count++)			// Transmitting the recieved data on UART
						{
							UART0_TxChar(Recieved_Data[count]); 					// Transmitting recieved data on UART
							Recieved_Data[count]=Clear_Array[0];					// Deleting the recieved data for next set of data
						}
							Reciver_Counter=0;														// Reset receiver counter
							UART0_SendString("\r\n");
				 }
			 else 																								// When no Data Recieved
				 { 
					 UART0_SendString("No data recieved \r\n");
					 LCD_Display(2,no_data); 													// Displaying predefined message on line 2 of LCD
				 }
		}				
					
				UART0_SendString("TRANSMISSION  ");
				UART0_TxNum(Loop_Count);
				UART0_SendString(" \r\n");		
				Loop_Count++;																				// Increment loop count
				Delay(DELAY_VALUE);
	}	
	
}
//=============================END OF MAIN FUNCTION ============================
