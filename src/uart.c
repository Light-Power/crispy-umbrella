#include "uart.h"
#include <REG52.H>
#include <STDIO.H>

unsigned char recv_data;
unsigned char recv_flag;
void UartInit(void) // 9600bps@11.0592MHz
{
    PCON &= 0x7F; // 波特率不倍速
    SCON = 0x50;  // 8位数据,可变波特率
    TMOD &= 0x0F; // 设置定时器模式
    TMOD |= 0x20; // 设置定时器模式
    TL1 = 0xFD;   // 设置定时初始值
    TH1 = 0xFD;   // 设置定时重载值
    ET1 = 0;      // 禁止定时器中断
    TR1 = 1;      // 定时器1开始计时
                  //
    EA = 1;       // 开启总中断
    ES = 1;       // 开启串口中断
    //
}

void sendByte(unsigned char dat) // 串口发送一个字节    这里数据不能用data ，因为data是保留字。(慎用ai帮写)
{
    SBUF = dat;
    while (TI == 0);
    TI = 0;
}

void sendString(unsigned char *str) // 串口发送字符串
{
    while (*str) {
        sendByte(*str);
        str++;
    }
}

char putchar(char c) // 串口发送一个字符
{
    sendByte(c);
    return c;
}

// 中断服务函数
void uart_ISR() interrupt 4
{
    if (RI == 1) {
        RI        = 0;
        recv_data = SBUF;
        recv_flag = 1; // 接收标志置1代表数据接收完毕
    }
}
