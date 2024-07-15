#ifndef __UART_H__
#define __UART_H__

extern unsigned char recv_data;
extern unsigned char recv_flag;

void UartInit(void); // 串口初始化

void sendByte(unsigned char dat); // 串口发送一个字节

void sendString(unsigned char *str); // 串口发送字符串

char putchar(char c); // 串口发送一个字符

#endif