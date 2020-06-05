#ifndef UART
#define UART 1
#define Size 25	

extern void UART_Initialize(void);
extern void UART0_TxChar(char ch);
extern void UART0_TxNum(int num);
extern void UART0_SendString(char *ch);
extern void UART0_HEX(char ch);
#endif
