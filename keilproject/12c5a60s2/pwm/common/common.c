#include "common.h"


/*******************************************************************************
* 函 数 名         : delay_us
* 函数功能		   : 延时函数，延时us
* 输    入         : i
* 输    出         : 无
*******************************************************************************/
void delay_us(uint32 i)         //实测单位20微秒
{
	#if STC12
    
    uint32 j;
    while(i--);

    #elif STM32
    
    uint32 temp;
	SysTick->LOAD=9*i;		 //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		 //使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;		   	 //清零计数器
	do
	{
		temp=SysTick->CTRL;		   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
    
    #endif
}

/*******************************************************************************
* 函 数 名         : delay_ms
* 函数功能		   : 延时函数，延时ms
* 输    入         : i
* 输    出         : 无
*******************************************************************************/
void delay_ms(uint32 i)         //实测
{
	#if STC12
    
    uint32 k,j; 
    for(k=i;k>0;k--) 
        for(j=190;j>0;j--); 
    
    #elif STM32
    
    uint32 temp;
	SysTick->LOAD=9000*i;	  //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		//使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;			//清零计数器
	do
	{
		temp=SysTick->CTRL;	   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
    
    #endif
}
