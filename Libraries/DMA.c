#include<lpc17xx.h>

#include "DMA.h"
#include "Buzzer.h"
#include "Timer.h"
#include "LCD.h"

//======================= DMA Channel Configuration (Memory To Memory) =========================

void DMAChannelConfig_MTM(int TotalSize,int Burst,int Channel,int Source,int Destination,int DataWidth)
{
		LPC_SC->PCONP |= (1 << 29);
		if(Channel ==	0)
		{
			LPC_GPDMACH0->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH0->DMACCConfig=0x00;
			LPC_GPDMACH0->DMACCSrcAddr=Source;
			LPC_GPDMACH0->DMACCDestAddr=Destination;
		}
		else if(Channel ==	1)
		{
			LPC_GPDMACH1->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH1->DMACCConfig=0x00;
			LPC_GPDMACH1->DMACCSrcAddr=Source;
			LPC_GPDMACH1->DMACCDestAddr=Destination;
		}
		else if(Channel ==	2)
		{
			LPC_GPDMACH2->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH2->DMACCConfig=0x00;
			LPC_GPDMACH2->DMACCSrcAddr=Source;
			LPC_GPDMACH2->DMACCDestAddr=Destination;
		}
		else if(Channel ==	3)
		{
			LPC_GPDMACH3->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH3->DMACCConfig=0x00;
			LPC_GPDMACH3->DMACCSrcAddr=Source;
			LPC_GPDMACH3->DMACCDestAddr=Destination;
		}
		else if(Channel ==	4)
		{
			LPC_GPDMACH4->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH4->DMACCConfig=0x00;
			LPC_GPDMACH4->DMACCSrcAddr=Source;
			LPC_GPDMACH4->DMACCDestAddr=Destination;
		}
		else if(Channel ==	5)
		{
			LPC_GPDMACH5->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH5->DMACCConfig=0x00;
			LPC_GPDMACH5->DMACCSrcAddr=Source;
			LPC_GPDMACH5->DMACCDestAddr=Destination;
		}
		else if(Channel ==	6)
		{
			LPC_GPDMACH6->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH6->DMACCConfig=0x00;
			LPC_GPDMACH6->DMACCSrcAddr=Source;
			LPC_GPDMACH6->DMACCDestAddr=Destination;
		}
		else if(Channel ==	7)
		{
			LPC_GPDMACH7->DMACCControl=(TotalSize<<TransferSize)|(Burst<<SourceBurst)|(Burst<<DestBurst)|(DataWidth<<SourceWidth)|(DataWidth<<DestWidth)|(1<<SourceIncrement)|(1<<DestIncrement);
			LPC_GPDMACH7->DMACCConfig=0x00;
			LPC_GPDMACH7->DMACCSrcAddr=Source;
			LPC_GPDMACH7->DMACCDestAddr=Destination;
		}
}

//==============================================================================================
//===================================DMA CHECK CHANNEL ENABLED==================================

void DMACheckChannelEnabled(int Channel)
{
		while(((LPC_GPDMA->DMACEnbldChns>>Channel) &	0x01)	== 1);
}

//==============================================================================================
//======================================= DMA ENABLE ===========================================
void DMAEnable(void)
{
			LPC_GPDMA->DMACConfig|=0x01;
}

//==============================================================================================
//======================================= DMA DISABLE ==========================================

void DMADisable(void)
{
			LPC_GPDMA->DMACConfig&=~(1<<0);
}

//==============================================================================================
//================================== DMA CHANNEL ENABLE ========================================

void DMAChannelEnable(int Channel)
{
	if(Channel==0)
		LPC_GPDMACH0->DMACCConfig|=0x01;
	
	else if(Channel==1)
		LPC_GPDMACH1->DMACCConfig|=0x01;
	
	else if(Channel==2)
		LPC_GPDMACH2->DMACCConfig|=0x01;
	
	else if(Channel==3)
		LPC_GPDMACH3->DMACCConfig|=0x01;
	
	else if(Channel==4)
		LPC_GPDMACH4->DMACCConfig|=0x01;
	
	else if(Channel==5)
		LPC_GPDMACH5->DMACCConfig|=0x01;
	
	else if(Channel==6)
		LPC_GPDMACH6->DMACCConfig|=0x01;
	
	else if(Channel==7)
		LPC_GPDMACH7->DMACCConfig|=0x01;
}

//==============================================================================================
//===================================== DMA CHANNEL DISBLE =====================================

void DMAChannelDisable(int Channel)
{
	if(Channel==0)
		LPC_GPDMACH0->DMACCConfig&=~(1<<0);
	
	else if(Channel==1)
		LPC_GPDMACH1->DMACCConfig&=~(1<<0);
	
	else if(Channel==2)
		LPC_GPDMACH2->DMACCConfig&=~(1<<0);
	
	else if(Channel==3)
		LPC_GPDMACH3->DMACCConfig&=~(1<<0);
	
	else if(Channel==4)
		LPC_GPDMACH4->DMACCConfig&=~(1<<0);
	
	else if(Channel==5)
		LPC_GPDMACH5->DMACCConfig&=~(1<<0);
	
	else if(Channel==6)
		LPC_GPDMACH6->DMACCConfig&=~(1<<0);
	
	else if(Channel==7)
		LPC_GPDMACH7->DMACCConfig&=~(1<<0);
}

//==============================================================================================
//=========================================	DMA Check ==========================================

void DMACheck(int Size, int Source,int Destination)
{
	int Loop_Count=0,count=0;
	char *Source_Addr,*Dest_Addr;
	Source_Addr=(char *)Source;
	Dest_Addr=(char *)Destination;
	
	for(Loop_Count=0;Loop_Count<Size;Loop_Count++)
	{
		if(*Source_Addr == *Dest_Addr)
			count++;
	
		Source_Addr++;
		Dest_Addr++;
	}
	
	if(count==Size)
		LCD_Display(1,"DMA OK");
	else
	{
		LCD_Display(1,"DMA ERROR");
		Delay(1000);
		Buzzer_Sound(3);
	}
}

//================================================================================================
//========================================== DMA TEST ============================================

void DMATest()
{
	
	#define message "Hello Ankit"
	#define SOURCE				0x10000500
	#define DESTINATION		0x2007FFA0
	#define CHANNEL 7
	#define BURST_SIZE 2
	#define WIDTH 0
	#define DMA_TRANSFER_SIZE 8
	char *Pointer;
	int count=0;
	Pointer=(char *)SOURCE;
	
		while(message[count]!='\0')
		{
			*Pointer=message[count];
			count++;
			Pointer++;
		}
	
		DMAChannelConfig_MTM(DMA_TRANSFER_SIZE,BURST_SIZE,CHANNEL,SOURCE,DESTINATION,WIDTH);
		DMAChannelEnable(CHANNEL);
		DMAEnable();
		DMACheckChannelEnabled(CHANNEL);
		DMACheck(DMA_TRANSFER_SIZE,SOURCE,DESTINATION);

}

//==================================================================================================
