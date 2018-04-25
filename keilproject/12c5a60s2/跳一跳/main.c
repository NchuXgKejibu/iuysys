#include <stdlib.h>
#include "include.h"

#define UP_angle 12		//舵臂抬起角度
#define DOWN_angle 10	//舵臂落下角度
 
uint8 get=0,begin=0;
uint8 count;		//输入计数器
uint8 str[6]={0}; 	//数字字符储存器	
uint16 time=65535;		//触屏时间
void Timer1Init(void);	 //50毫秒@11.0592MHz

int main()
{
	uint16 dis;				//距离
	
	Timer1Init();			//定时器1初始化
	pwm_init_T0(PCA_0,50); 	//PWM初始化
	usart_init(USART1,BUAD);//初始化串口
	
	ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch
	while(1)
	{
		if(get==1)
		{	
			uint8 i;
			dis = atoi(str);		//字符串转换为数字
			time = dis*200;		//计算触控时间
			begin =1;				//开始标志
			printf("距离:%d\t触控时间:%d\n",dis,time);
			TF1=0;
			TL1 = 0x00;		//设置定时初值
			TH1 = 0xDC;		//设置定时初值
			get = 0;				//结束一次距离输入

		}
		if(begin)
		{
			pwm_duty(PCA_0,DOWN_angle);
			TR1 =1;					//打开定时器
		} 
		else
		{

			pwm_duty(PCA_0,UP_angle);
			REN =1;
			TR1=0;
		}

	}		
}

void Timer1Init(void)		//10毫秒@11.0592MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x00;		//设置定时初值
	TH1 = 0xDC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 0;		//定时器1开始计时
	ET1 =1;					//Enable T1 interrupt
}


/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 1
{
	if (RI)
    {	
		
		RI = 0;             //Clear receive interrupt flag
        str[count] = SBUF; 
		count ++;
		if(str[count-1]=='.')
		{
			str[count]='\0';
			get=1; 
			count = 0;
			REN =0;
		}       
    }
}
/* Timer0 interrupt routine */
void tm1_isr() interrupt 3 using 1
{
    static uint16 i=0;
	TL1 = 0x00;		//设置定时初值
	TH1 = 0xDC;		//设置定时初值
	i ++;
	if((i*10) >= time)
	{
		begin =0;
		i = 0 ;
		printf("\n请输入距离!\n");
	}
}









