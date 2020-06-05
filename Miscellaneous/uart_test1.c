#include<lpc17xx.h>
#include "Timer.h"
#include "UART.h"
#include "PLL.h"
#include "LCD.h"

//================================ GLOBAL VARIABLES =======================================
char Recieved_Data[Size];
int Reciver_Counter=0;
//=========================================================================================

//================================ LOCAL FUNCTIONS ========================================
void Clear_Recieved_Data(void)
{      
int counter=0;
char Clear_Array[]=(" ");

       while(counter<Reciver_Counter)
			  {
					Recieved_Data[counter]=Clear_Array[0];
					counter++;
			  }
}
//=========================================================================================

//=============================== UART INTERRUPT HANDLER ==================================
void UART0_IRQHandler(void)
{
	char IIRval,LSRval;
IIRval=LPC_UART0->IIR;																			// For identifing the source of interrupt
			
		if( ((IIRval>>1)&0x07) == RDA) 													// If received data is available
		{
		  Recieved_Data[Reciver_Counter]=LPC_UART0->RBR;       	// Retrieve data from RBR and clear interrupt
			Reciver_Counter++;																		// Increment the receiver counter
				
			
				if(Reciver_Counter==Size)														// If received value is equal to count
			Reciver_Counter=0;																		// Reset the receiver counter
		}
		
		else if( ((IIRval>>1)&0x07) == RLS)											// Receive L:ne Status Interrupt
		{
			LSRval=LPC_UART0->LSR;
			LSRval=LSRval>>1;
			
			
			if((LSRval&0xF) == 0x01) 															// Check for overrun error due to RBR
				UART0_SendString("Overrun Error. WARNING:  DATA LOSS \r\n");
			
			else if((LSRval&0xF)== 0x02) 													// Check for Parity error in transmisson
				UART0_SendString("Parity error. WARNING:  Error in transmission \r\n");
			
			else if((LSRval&0xF)== 0x04) 													// Check for Framing error 
				UART0_SendString("Framing error. WARNING:  Data lost in transmission \r\n");
			
			else if((LSRval&0xF)== 0x08) 													// Check for Break error due to no transmission
				UART0_SendString("Break error. RECEIVE FUNCTION TERMINATED \r\n");
		}

		else if( ((IIRval>>9)&0x01)==0x01) 											// If Auto baud timeout
		LPC_UART0->ACR|=(1<<9);	          											// Clear interrupt
		
		else if( ((IIRval>>8)&0x01)==0x01) 									 		// If Auto baud successful
					LPC_UART0->ACR|=(1<<8);												 		// Clear  Interrupt
}
//=========================================================================================

//==================================== MAIN FUNCTION ======================================
int main()
{
	int Loop_Count=0,count;
  PLL_Init(75);																							// Initialize the PLL for CPU Clock Frequency
	Timer_Init(2);																						// Initialize the timer with pre-defined pre-scalar values
 	UART_Initialize(38400);																		// Initialize the UART for 38400
	NVIC_EnableIRQ(UART0_IRQn);																// Enabele UART0 Interrupt
	Delay(1);
	UART0_SendString("\r\n Hi Ankit \r\n");
	Delay(1);
	while(1)
	{
		
		if((Loop_Count%10)==0 && Loop_Count!=0)									// Check for recieved data on every 10th Transmission
		{
			 if(Reciver_Counter>0)																// If Data recieved
			 {
					UART0_SendString("Recieved Data:  ");
				  count=0;
					while(count<Reciver_Counter)											// Display received data
					{
						UART0_TxChar(Recieved_Data[count]);
						count++;
					}
				
					Clear_Recieved_Data();														// Clear received data array
					Reciver_Counter=0;																// Reset received counter
					UART0_SendString("\r\n");
		  }
			else
			{ 
					Clear_Recieved_Data();
					UART0_SendString("No data recieved \n");
			}
		}
				UART0_SendString("TRANSMISSION  ");
				UART0_TxNum(Loop_Count);
				UART0_SendString(" \r\n ");		
				Loop_Count++;																				// Increment loop counter
		    Delay(500000);
	}
}
//================================ END OF MAIN FUNCTION ===================================
