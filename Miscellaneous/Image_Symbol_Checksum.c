#include<lpc17xx.h>

#include "PLL.h"
#include "LCD.h"
#include "Timer.h"
#include "Buzzer.h"

extern unsigned int Image$$ER_IROM1$$Base;
extern unsigned int Image$$ER_IROM1$$Limit;
extern unsigned int __heap_base;
int main()
{
	char *ExecutionRegionAddress,*ExecutionRegionAddressFinal;
	int *Pointer;
	int Checksum=0,Count=0;
	Pointer=(int *)0x10000FF0;
	PLL_Init(100);
	Timer_Init(99999);
	LCD_Init();
	Buzzer_Init();
	ExecutionRegionAddress=(char *)&Image$$ER_IROM1$$Base;
	ExecutionRegionAddressFinal=(char*)	&Image$$ER_IROM1$$Limit;
	LCD_Display(1,"Address of base:");
	LCD_Display_Num(2,(int)ExecutionRegionAddress);
	Delay(5000);
	
	LCD_Display(1,"Address limit is:");
	LCD_Display_Num(2,(int)ExecutionRegionAddressFinal);
	Delay(5000);
	
	for(ExecutionRegionAddress=(char *)&Image$$ER_IROM1$$Base;		ExecutionRegionAddress<=ExecutionRegionAddressFinal;		ExecutionRegionAddress++)
		{
			Checksum+= (int) *ExecutionRegionAddress;
			Count++;
		}
	
	LCD_Display(1,"Count is");
	LCD_Display_Num(2,Count);
	Delay(5000);
		
	LCD_Display(1,"Checksum is");
	LCD_Display_Num(2,Checksum);
	*Pointer=Checksum;
}
