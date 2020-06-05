#ifndef UART
#define UART 1

extern void UART0_TxNum(int);
extern void UART0_TxChar(char);
extern void UART0_POST(void);
extern void UART0_SendString(char *ch);
extern void UART_Init(void);
#endif
