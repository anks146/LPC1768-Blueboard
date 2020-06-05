#include<lpc17xx.h>
#include "Timer.h"
#include "UART_Autobaud.h"
#include "PLL.h"
#include "LCD.h"


#define DELAY_VALUE 900
#define PRESCALAR_VALUE 99999
#define CCLK_VALUE 100 // In MHz
#define message1 "Total no of Recd."

//=============================== GLOBAL VARIABLES ============================================
int Reciever_Counter=0,Reciever_Array_Head=0;
char Recieved_Data[Size];
//=============================================================================================

//============================ UART INTERRUPT HANDLER =========================================
void UART0_IRQHandler(void)
{
		char IIRval; 
		IIRval=LPC_UART0->IIR; 													//To identify the interrupt source

		if(((IIRval>>1)&0x07) == 0x02) 									// If receved data is available
			{
					if(Reciever_Array_Head==Size) 						// If Array is full and the next character recieved will be outside the range of the Array Size
								Reciever_Array_Head=0;

					Recieved_Data[Reciever_Array_Head]=LPC_UART0->RBR;	//Store received data and clear the interrupt 
					Reciever_Counter++;   										// Increment receiver count
					Reciever_Array_Head++;										// Increment the position of the next character 
			}

		else if( ((IIRval>>8)&0x01)==0x01) 							// If Auto baud successful
					LPC_UART0->ACR|=(1<<8);										// Clear  Interrupt

		else if( ((IIRval>>9)&0x01)==0x01) 							// If Auto baud Timeout
					LPC_UART0->ACR|=(1<<9);	          				// Clear interrupt

}
//===================================== END OF INTERRUPT HANDLER ==============================

//===================================== LOCAL FUNCTIONS =======================================

void HardwareFlowControl()
{
	LPC_PINCON->PINSEL4&=~(3<<24); 										// Reset pin P2.12
	LPC_PINCON->PINSEL4|=(1<<24);	 										// Set P2.12 as EINT2
	//LPC_SC->EXTMODE|=(1<<2);
	LPC_SC->EXTMODE&=~(1<<2);   	 										//  Edge sensitive mode for interrupt
	LPC_SC->EXTPOLAR&=~(1<<2);		 										//  Falling edge for interrupt
	//LPC_SC->EXTPOLAR|=(1<<2);
	NVIC_EnableIRQ(EINT2_IRQn);		 										// Enable Interrupt 
}
//======================================== END OF FUNCTION =====================================

//=================================== EXTERNAL INTERRUPT HANDLER ===============================
void EINT2_IRQHandler()  				 										// Interrupt Handler for EINT2
{
	if(LPC_UART0->TER==0X80)
		LPC_UART0->TER=0;																// Disable transmission of UART
	else
		LPC_UART0->TER=0x80;														// Enable transmission of UART

	LPC_SC->EXTINT|=(1<<2);		 		 										// Clear interrupt flag
}
//==================================== END OF INTERRUPT HANDLER =================================

//========================================= MAIN FUNCTION =======================================

int main()
{
	int Loop_Count=0,count,MAX_Val=0;
	PLL_Init(CCLK_VALUE); 															// Initialize PLL
	Timer_Init(PRESCALAR_VALUE); 												// Initialize timer for desired PR
	LCD_Init();																					// Initialize LCD
	LCD_Display(1,AUTOBAUD_Message);
	UART_Initialize(); 																	// Initialize UART for specified PLL
	LCD_Display(1,message1);
	NVIC_EnableIRQ(UART0_IRQn); 												// Enable interrupt
	HardwareFlowControl(); 															// Initialize for external interrupt
	Delay(1);
	UART0_SendString("Hi Ankit\r\n"); 									// Send some data for start new transmission
	Delay(1);
	Reciever_Counter=0;
	Reciever_Array_Head=0;
	while(1)
	{
		if((Loop_Count%10)==0 && Loop_Count!=0 ) 					// Checking for recieved data on every 10th Transmission
		{
			 if(Reciever_Counter>0) 												// When Data recieved
				 {
				   UART0_SendString("Total number of characters recieved:\t");
					 LCD_Display_Num(2,Reciever_Counter); 			// Display the total number of characters received
					 UART0_TxNum(Reciever_Counter);							// Transmitting the total number of characters received
					        
						 if(Reciever_Counter<Size ) 							// To displaying all the received data and no NULL values
												MAX_Val = Reciever_Array_Head;
						 else
												MAX_Val=Size;

					 UART0_SendString(        "\r\nRecieved Data:  ");
					 
					 for(count=0;count<MAX_Val;count++) 				// Transmit the recieved data on UART
							UART0_TxChar(Recieved_Data[count]);

					 UART0_SendString("\r\nFirst Character :\t");
					 UART0_TxChar(Recieved_Data[0]);						//	Transmit the first character of received array
					 UART0_SendString("\t Last Character: \t");
					 UART0_TxChar(Recieved_Data[MAX_Val-1]);		//	Transmit the last character of received array
					 UART0_SendString("\r\n");
				 }

			 else // When no Data Recieved
			 {
					 UART0_SendString("No data recieved \r\n");
					 LCD_Display_Num(2,0);
			 }
		}
								
	UART0_SendString("TRANSMISSION  ");
	UART0_TxNum(Loop_Count);
	UART0_SendString(" \r\n");
	Loop_Count++;																				// Incrementing the loop count after each loop
	Delay(DELAY_VALUE); 																// Delay between consecutive loops
	}	
}
//======================================== END OF MAIN FUNCTION =================================
