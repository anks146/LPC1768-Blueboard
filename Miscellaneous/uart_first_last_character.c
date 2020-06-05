#include<lpc17xx.h>
#include "Timer.h"
#include "UART_Autobaud.h"
#include "PLL.h"
//#include "LCD.h"

#define DELAY_VALUE 900
#define PRESCALAR_VALUE 99999
#define CCLK_VALUE 100 // In MHz
#define BAUD_RATE 115200

//================================== GLOBAL VARIABLES ================================
int Reciver_Counter=0;
char Recieved_Data[Size];
//====================================================================================

//=============================== UART INTERRUPT HANDLER =============================
void UART0_IRQHandler(void)
{
	char IIRval;
	IIRval=LPC_UART0->IIR;
	
	if(((IIRval>>1)&0x07) == 0x02) // If receved data is available
	{
			Recieved_Data[Reciver_Counter]=LPC_UART0->RBR;
			Reciver_Counter++;

			if(Reciver_Counter==Size)
				Reciver_Counter=0;
	}
	else if( ((IIRval>>8)&0x01)==0x01) // If Auto baud successful
			LPC_UART0->ACR|=(1<<8);						// Clear  Interrupt
				
	else if( ((IIRval>>9)&0x01)==0x01) // If Auto baud Timeout
		LPC_UART0->ACR|=(1<<9);	          // Clear interrupt

}
//====================================================================================

//================================== MAIN FUNCTION ===================================
int main()
{
	int Loop_Count=0,count;
  PLL_Init(CCLK_VALUE);																				// Initialize the PLL for CPU Clock Frequency
	Timer_Init(PRESCALAR_VALUE); 																// Initialize the timer with pre-defined pre-scalar values
 	UART_Initialize(); 																					// Initialize UART for AutoBaud
	NVIC_EnableIRQ(UART0_IRQn); 																// Enable UART0 interrupt
	Delay(1);
	UART0_SendString("Hi Ankit\r\n"); 
	Delay(1);
	Reciver_Counter=0;																					// Reset receiver counter
	while(1)
	{
		if((Loop_Count%10)==0 && Loop_Count!=0 ) 									// Check for received data on every 10th Transmission
		{
			 if(Reciver_Counter>0 && Reciver_Counter!=count) 				// When Data received
				 {
				   UART0_SendString("Number of characters recieved:\t");
					 UART0_TxNum(Reciver_Counter);											// Transmit total number of character received
					 
					 UART0_SendString("\r\nRecieved Data:\r\n");
					 UART0_SendString("First Character :\t");
					 UART0_TxChar(Recieved_Data[0]);										//	Transmit the first character of received array
					 UART0_SendString("\t Last Character: \t");
					 UART0_TxChar(Recieved_Data[Reciver_Counter-1]);		//	Transmit the last character of received array
					 
					 count=Reciver_Counter;
				   UART0_SendString("\r\n");
					}
			 else // When no Data Recieved
				 UART0_SendString("No data recieved \r\n");
		}				
					
				UART0_SendString("TRANSMISSION  ");
				UART0_TxNum(Loop_Count);
				UART0_SendString(" \r\n");		
				Loop_Count++;																					// Increment loop count after each loop 
				Delay(DELAY_VALUE);
	}	
}
//=============================== END OF MAIN FUNCTION ===============================
