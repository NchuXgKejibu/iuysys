#ifndef _PWM_H
#define _PWM_H
#include<reg52.h>


extern char MOTORSpeed;
extern unsigned int MOTORCount,ServoCount,ServoAngle,Servoflag;

sbit PWM0	=	P0^4;			//PWM输出引脚
sbit PWM1	=	P0^5;
sbit Servo0	=	P0^2;			//舵机
sbit Servo1	=	P0^3;

void PWM_Init(void);					//PWM初始化
void MOTOR(char Speed);					//电机控制
void ServoControl(unsigned char angle);	//舵机角度控制
void delay_ms(unsigned int time);		//延时



#endif