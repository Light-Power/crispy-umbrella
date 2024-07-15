#include "uart.h"
#include <REG52.H>
#include <STDIO.H>

unsigned char recv_data;
unsigned char recv_flag;
void UartInit(void) // 9600bps@11.0592MHz
{
    PCON &= 0x7F; // �����ʲ�����
    SCON = 0x50;  // 8λ����,�ɱ䲨����
    TMOD &= 0x0F; // ���ö�ʱ��ģʽ
    TMOD |= 0x20; // ���ö�ʱ��ģʽ
    TL1 = 0xFD;   // ���ö�ʱ��ʼֵ
    TH1 = 0xFD;   // ���ö�ʱ����ֵ
    ET1 = 0;      // ��ֹ��ʱ���ж�
    TR1 = 1;      // ��ʱ��1��ʼ��ʱ
                  //
    EA = 1;       // �������ж�
    ES = 1;       // ���������ж�
    //
}

void sendByte(unsigned char dat) // ���ڷ���һ���ֽ�    �������ݲ�����data ����Ϊdata�Ǳ����֡�(����ai��д)
{
    SBUF = dat;
    while (TI == 0);
    TI = 0;
}

void sendString(unsigned char *str) // ���ڷ����ַ���
{
    while (*str) {
        sendByte(*str);
        str++;
    }
}

char putchar(char c) // ���ڷ���һ���ַ�
{
    sendByte(c);
    return c;
}

// �жϷ�����
void uart_ISR() interrupt 4
{
    if (RI == 1) {
        RI        = 0;
        recv_data = SBUF;
        recv_flag = 1; // ���ձ�־��1�������ݽ������
    }
}
