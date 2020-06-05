#include<lpc17xx.h>
#include "Timer.h"
#include "UART_Autobaud.h"
#include "PLL.h"
#include "LCD.h"

#define DELAY_VALUE 900
#define PRESCALAR_VALUE 999
#define CCLK_VALUE 100 // In MHz
#define message1 "Total no of Recd."
//================================= GLOBAL VARIABLES =====================================
int Reciever_Counter=0,Reciever_Array_Head=0;
char Recieved_Data[Size];
//========================================================================================

//================================= SOFTWARE FLOW CONTROL ================================
void SoftwareFlowControl()
{
		int Counter;
		char message2[]=("Memory is Full");
		Reciever_Array_Head=0;															// Reset the array counter
		LCD_Display(1,message2);
		LCD_Clear(2);																				// Clear the second line of LCD
		UART0_SendString("\r\nMemory Full. Please wait for 60 seconds before continuing transmission to avoid data LOSS.\r\n");
		Delay(10000);																				// 1 Second Delay
					
			for(Counter=50;Counter>0;Counter=(Counter-10))
			{
				UART0_SendString("Please wait ");
				UART0_TxNum(Counter);
				UART0_SendString(" seconds before continuing transmission\r\n");
				Delay(10000);
			}
		
		UART0_SendString("Ready to recieve data. Please continue transmission AFTER: ");
									
			for(Counter=(Size-10);Counter<Size;Counter++) 		// Tranmit the last 10 characters received
				UART0_TxChar(Recieved_Data[Counter]);	
				
		UART0_SendString("\r\n");
		LCD_Display(1,message1);
		LCD_Display_Num(2,Reciever_Counter);								// Display the total number of characters received
									
}
//========================================================================================
//============================== UART INTERRUPT HANDLER ==================================
void UART0_IRQHandler(void)
{
		char IIRval;
		IIRval=LPC_UART0->IIR;															 // For identifing the source of interrupt
	
		if(((IIRval>>1)&0x07) == 0x02)											 // If receved data is available
			{
					if(Reciever_Array_Head==Size) 							   // If Array is full and the next character recieved will be outside the range of the Array Size
								Reciever_Array_Head=0;
										
					Recieved_Data[Reciever_Array_Head]=LPC_UART0->RBR;	// Store the received data and resetting the interrupt flag
					Reciever_Counter++;														 // Increment the total number of received character
					Reciever_Array_Head++;												 // Increment the position of next character in the array
			}			
	
		else if( ((IIRval>>8)&0x01)==0x01) 									 // If Auto baud successful
					LPC_UART0->ACR|=(1<<8);												 // Clear  Interrupt
		
		else if( ((IIRval>>9)&0x01)==0x01) 									 // If Auto baud Timeout
					LPC_UART0->ACR|=(1<<9);	          						 // Clear interrupt
}
//========================================================================================

//================================== MAIN FUNCTION =======================================
int main()
{
	int Loop_Count=0,count,MAX_Val=0;
	PLL_Init(CCLK_VALUE); 																// Initialize the PLL for CPU Clock Frequency
	Timer_Init(PRESCALAR_VALUE); 													// Initialize the timer with pre-defined pre-scalar values
	LCD_Init();																						// Initialize the LCD
	LCD_Display(1,AUTOBAUD_Message);
	UART_Initialize(); 																		// Initialize UART for AutoBaud
	LCD_Display(1,message1);
	NVIC_EnableIRQ(UART0_IRQn);														// Enable UART0 interrupt
	UART0_SendString("Hi Ankit\r\n"); 
	Reciever_Counter=0;																		// Reset receiver counter
	Reciever_Array_Head=0;
	while(1)
	{
		if((Loop_Count%10)==0 && Loop_Count!=0 ) 						// Check for recieved data on every 10th Transmission
		{
			 if(Reciever_Counter>0)														// When Data recieved
				 {
				   UART0_SendString("Total number of characters recieved:\t");
					 LCD_Display_Num(2,Reciever_Counter);					// Display total number of character received
					 UART0_TxNum(Reciever_Counter);								// Transmit total number of character received
					        
					 if(Reciever_Counter<Size )										// Display array till valid data only
											MAX_Val = Reciever_Array_Head;
					 else
									    MAX_Val=Size;
					 					 
					 UART0_SendString("\r\nRecieved Data:  ");
					 
					 for(count=0;count<MAX_Val;count++) 					// Transmit the recieved data on UART
							UART0_TxChar(Recieved_Data[count]);
					 
					 UART0_SendString("\r\nFirst Character :\t");
					 UART0_TxChar(Recieved_Data[0]);							//	Transmit the first character of received array
					 UART0_SendString("\t Last Character: \t");
					 UART0_TxChar(Recieved_Data[MAX_Val-1]);			//	Transmit the last character of received array
					 UART0_SendString("\r\n");
				 }
			 else // When no Data Recieved
				{
					 UART0_SendString("No data recieved \r\n");
					 LCD_Display_Num(2,0);
				}
		}
				if(Reciever_Array_Head==Size) 									// If Array is full and the next character recieved will be outside the range of the Array Size
					SoftwareFlowControl();
				
				UART0_SendString("TRANSMISSION  ");
				UART0_TxNum(Loop_Count);
				UART0_SendString(" \r\n");
				Loop_Count++;																		// Incrementing the Loop count for next transmission
				Delay(DELAY_VALUE);
	}	
}
//================================ END OF MAIN FUNCTION ==================================
