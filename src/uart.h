#ifndef __UART_H__
#define __UART_H__

extern unsigned char recv_data;
extern unsigned char recv_flag;

void UartInit(void); // ���ڳ�ʼ��

void sendByte(unsigned char dat); // ���ڷ���һ���ֽ�

void sendString(unsigned char *str); // ���ڷ����ַ���

char putchar(char c); // ���ڷ���һ���ַ�

#endif