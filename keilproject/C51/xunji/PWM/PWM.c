#include"PWM.h"


char MOTORSpeed=0,Angle,Angle1=0x18,AngleFlag,AngleFlag1=4,speed;
unsigned int MOTORCount=0,ServoCount=0,ServoAngle=90,Servoflag=0;

void PWM_Init()
{
	TMOD|=0x01;			//设置定时器0工作方式1,定时器1工作方式1
	
	T2MOD|=0x00;		//设置定时器2工作方式16位自动重载
	T2CON|=0X00;
	
	TH0=0xff;			//
	TL0=0xa4;			
	
	RCAP2H=0xff;		//定时器2自动重载数值
	RCAP2L=0xd2;        //5ms

	
	PT0=1;				//T0高中断级别
	
	EA=1;				//开总中断
	
	ET0=1;				//允许T0中断
	ET2=1;				//允许T2中断

	PWM0=0;				//电机输出引脚
	PWM1=0;
	
	Servo0=0;			//转向电机
	Servo1=0;

	TR0=0;				//关闭定时器0
	TR2=1;				//开启定时器2
}

void MOTOR(char Sp)
{
	speed=Sp;
    speed=speed<0?0:speed;
    speed=speed>100?100:speed;
    PWM1=0;
    		
}

void ServoControl(unsigned char angle)
{ 
	ServoAngle=180-angle;
	Servo1=0;
    		
}


void delay_ms(unsigned int time)
{
	int icd,jcd;
	for(icd=0;icd<time;icd++)
		for(jcd=0;jcd<110;jcd++);
}
/***************************************************
void PWM_interrupt(void) interrupt 5
{
	TF2=0;
	MOTORCount++;
    Angle=(~P2)&0x7e;
	MOTORCount=MOTORCount>100?1:MOTORCount;
	
	if(MOTORCount<MOTORSpeed)
		PWM0=1;
	else
		PWM0=0;	
}

***************************************************/
/***************************************************
void Servo_interrupt(void) interrupt 1
{
	TH0=0xff;			//500hz
	TL0=0xa4;							
	ServoCount++;
    //Angle=(~P2)&0x7e;
    //if(ServoCount>200)
    {
        ServoCount=1;
        if(P_Angle>ServoAngle)
        {
            P_Angle--;
            if(P_Angle==ServoAngle)
               P_Angle=ServoAngle; 
        }
        else if(P_Angle<ServoAngle)
        {
            P_Angle++;
            if(P_Angle==ServoAngle)
               P_Angle=ServoAngle;
        }
    }
    //P_Angle=ServoAngle>P_Angle?P_Angle++;
	ServoCount=ServoCount>200?1:ServoCount;
    if(ServoCount<(P_Angle/9)+5)
		Servo0=1;
	else
		Servo0=0;
}
***************************************************/

