#include <reg52.h>
#include "serial.h"
#include "PWM.h"
/******************************************
			全局变量
*******************************************/
unsigned char MainFlag=0;						//选择运行的模式函数

unsigned char Serial_flag=0;					//串口变量
char Serial_dat=0;

int main(void)
{	

	Serial_Init();			//串口初始化
	PWM_Init();				//PWM初始化  
	while(1) 
	{		
	
		if(Serial_flag)
		{
			switch(Serial_dat)
			{
				case 'A':
						{
							MOTORSpeed+=10;
							if(MOTORSpeed>=100)
								MOTORSpeed=100;
						}
						break;
				case 'B':
						{
							MOTORSpeed-=10;
							if(MOTORSpeed<=-100)
								MOTORSpeed=-100;
						};
						break;
				case 'C':
						{
							MOTOR(0);
							ServoControl(90);
						}
						break;
				case 'D':
						MOTORSpeed=100;
						break;
				case 'a':				//向前
						{
							ServoControl(90);
						}
						break;
				case 'e':				//向后
						{
							MOTOR(-MOTORSpeed);
							ServoControl(90);
						}
						break;
				case 'c':				//完全左
						{
							ServoControl(0);	
						}
						break;
				case 'g':				//完全右
						{
							ServoControl(180);
						}
						break;
				case 'b':				//左前
						{
							ServoControl(45);
						}
						break;
				case 'h':				//右前
						{
							ServoControl(135);
						}
						break;
				case 'd':				//左后
						{
							ServoControl(45);
						}
						break;
				case 'f':				//右后
						{
							ServoControl(135);
						}
						break;

				
			}
			//SBUF=Serial_dat;
			Serial_flag=0;
		}
		MOTOR(MOTORSpeed);	
	}     	  
	
}

/**********************************************
				中断函数
***********************************************/
void Serial_Receive(void) interrupt	4
{
		if(RI)
		{
			RI=0;
			Serial_dat=SBUF;
			Serial_flag=1;
		}
}

void Servo_interrupt(void) interrupt 1
{
	TH0=0xff;			//80us
	TL0=0x9c;							
	ServoCount++;
	if(ServoAngle<90)
	{
		if(ServoCount<(90-ServoAngle)*15)	
			Servo0=1;
		else
		{
			Servoflag++;
			Servo0=0;
			Servo0=1;	
			Servo0=0;
			if(Servoflag>2500)
				TR0=0;
		}
	}
	else
	{
		if(ServoCount<(ServoAngle-90)*20)
			Servo1=1;
		else
		{
			Servoflag++;
			Servo1=0;
			Servo1=1;	
			Servo1=0;
			if(Servoflag>2500)
				TR0=0;  
		}	
	}

}


void PWM_interrupt(void) interrupt 5
{
	TF2=0;
	MOTORCount++;
	MOTORCount=MOTORCount>100?1:MOTORCount;
	if(MOTORSpeed>=0)
	{
		if(MOTORCount<MOTORSpeed)
			PWM0=1;
		else
			PWM0=0;	
	}
	else
	{
		if(MOTORCount>(100+MOTORSpeed))
			PWM1=1;
		else
			PWM1=0;
	}
}

 