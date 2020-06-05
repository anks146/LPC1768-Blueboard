#include<lpc17xx.h>
#ifndef SPI
#define SPI

void SPI_Init(void);
void Send_Data(char c);
char Receive_Data(void);
uint8_t Data_Transfer(void);
void Send_SPI(char *c);
int Receive_SPI(int num);

#endif
