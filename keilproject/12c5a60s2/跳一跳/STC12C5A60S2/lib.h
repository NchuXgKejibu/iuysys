#ifndef __LIB_H__
#define __LIB_H__

#include <intrins.h>
#include <stdio.h>
#include "include.h"



//=========================================================
typedef enum
{
    GPIO_OUT_LP,            //弱上拉
    GPIO_OUT_PP,            //推挽输出
    GPIO_OUT_HR,            //高阻
    GPIO_OUT_OD             //开漏
        
}GPIO_OUT_MODE;             //输出模式枚举
typedef enum
{
    GPIO_Pin_0=0x01,
    GPIO_Pin_1=0x02,
    GPIO_Pin_2=0x04,
    GPIO_Pin_3=0x08,
    GPIO_Pin_4=0x10,
    GPIO_Pin_5=0x20,
    GPIO_Pin_6=0x40,
    GPIO_Pin_7=0x80,
    GPIO_Pin_ALL=0xff
}GPIO_chx;                  //引脚号枚举

typedef enum
{
    GPIO_P0,
    GPIO_P1,
    GPIO_P2,
    GPIO_P3,
    GPIO_P4,
    GPIO_P5
}GPIO_n;                    //端口号枚举

//=========================================================
#define printf_usart USART1         //printf函数端口号

//串口相关的枚举
typedef enum
{
    USART1,
    USART2
}USARTn_e;          //串口号枚举

//=========================================================
//ADC相关的枚举
typedef enum
{
     ADC_0,
     ADC_1,
     ADC_2,
     ADC_3,
     ADC_4,
     ADC_5,
     ADC_6,
     ADC_7,
     ADC_ALL=0x07
}ADC_ch;            //ADC通道号枚举

typedef enum
{
    ADC_POWER   =0x80,            //ADC power control bit
    ADC_FLAG    =0x10,            //ADC complete flag
    ADC_START   =0x08,            //ADC start control bit
    ADC_SPEEDLL =0x00,
    ADC_SPEEDL  =0x20,
    ADC_SPEEDH  =0x40,
    ADC_SPEEDHH =0x60
}ADC_CMD;         //ADC命令枚举
//=========================================================
//PCA相关的枚举
typedef enum
{
     PCA_0,
     PCA_1
}PCA_n;         //PCA模块枚举
//========================================================
extern void gpio_out_mode(GPIO_n port,GPIO_chx gpio_pin,GPIO_OUT_MODE mode);//GPIO输出模式配置

//=========================================================
extern bit usart_init(USARTn_e usartn,uint32 baud );//初始化串口

extern char putchar(char c);   //重定向putchar函数

extern bit usart_send(USARTn_e usartn,uint8 Data); // 串口发送数据

extern uint8 usart_get(USARTn_e usartn); // 串口接收数据,查询方式

extern void usart_putbuff(USARTn_e usartn,uint8 *buff,uint32 len);   // 发送len个字节BUFF

extern void usart_putstr(USARTn_e usartn,uint8 *str);  //发送字符串

extern void usart_sware(USARTn_e usartn,void *wareaddr,uint32 waresize); // 虚拟示波器


//============================================================
extern void adc_init(ADC_ch adc_ch,ADC_CMD cmd);                     //ADC通道初始化

extern uint16 adc_get(ADC_ch adc_ch,ADC_CMD cmd);                                //获取ADC转换的值,查询方式

//============================================================

extern void pwm_init_NT0(PCA_n pca,uint8 div);                  //pWM初始化,不使用T0产生时钟

extern void pwm_init_T0(PCA_n pca,uint32 freq);                  //使用T0产生时钟

extern void pwm_duty(PCA_n pca,uint8 duty);                //pwm占空比

extern void pwm_perc(PCA_n pca,uint8 perc);                 //百分比输入占空比

extern void servo(PCA_n pca,uint8 ang);					//舵机角度

//============================================================





#endif