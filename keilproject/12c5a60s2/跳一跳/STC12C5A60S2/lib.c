
#include "lib.h"
//===================================
//函数名        :GPIO输出模式配置
//函数功能      :
//输入          :
//输出          :
//===================================
void gpio_out_mode(GPIO_n port,GPIO_chx gpio_pin,GPIO_OUT_MODE mode)
{    
    if(port==GPIO_P0)
    {
        switch(mode)
        {
            case GPIO_OUT_LP:
            {
                P0M0&=~gpio_pin;
                P0M1&=~gpio_pin;
            }break;
            case GPIO_OUT_PP:
            {
                P0M0|=gpio_pin;
                P0M1&=~gpio_pin;
            }break;
            case GPIO_OUT_HR:
            {
                P0M0&=~gpio_pin;
                P0M1|=gpio_pin;
            }break;
            case GPIO_OUT_OD:
            {
                P0M0|=gpio_pin;
                P0M1|=gpio_pin;
            }break;
        }
    }
    else if(port==GPIO_P1)
    {
        switch(mode)
        {
            case GPIO_OUT_LP:
            {
                P1M0&=~gpio_pin;
                P1M1&=~mode;
            }break;
            case GPIO_OUT_PP:
            {
                P1M0|=gpio_pin;
                P1M1&=~mode;
            }break;
            case GPIO_OUT_HR:
            {
                P1M0&=~gpio_pin;
                P1M1|=mode;
            }break;
            case GPIO_OUT_OD:
            {
                P1M0|=gpio_pin;
                P1M1|=mode;
            }break;
        }
    }
    else if(port==GPIO_P2)
    {
        switch(mode)
        {
            case GPIO_OUT_LP:
            {
                P2M0&=~gpio_pin;
                P2M1&=~mode;
            }break;
            case GPIO_OUT_PP:
            {
                P2M0|=gpio_pin;
                P2M1&=~mode;
            }break;
            case GPIO_OUT_HR:
            {
                P2M0&=~gpio_pin;
                P2M1|=mode;
            }break;
            case GPIO_OUT_OD:
            {
                P2M0|=gpio_pin;
                P2M1|=mode;
            }break;
        }
    }
    else if(port==GPIO_P3)
    {
        switch(mode)
        {
            case GPIO_OUT_LP:
            {
                P3M0&=~gpio_pin;
                P3M1&=~mode;
            }break;
            case GPIO_OUT_PP:
            {
                P3M0|=gpio_pin;
                P3M1&=~mode;
            }break;
            case GPIO_OUT_HR:
            {
                P3M0&=~gpio_pin;
                P3M1|=mode;
            }break;
            case GPIO_OUT_OD:
            {
                P3M0|=gpio_pin;
                P3M1|=mode;
            }break;
        }
    }
    else if(port==GPIO_P4)
    {
        switch(mode)
        {
            case GPIO_OUT_LP:
            {
                P4M0&=~gpio_pin;
                P4M1&=~mode;
            }break;
            case GPIO_OUT_PP:
            {
                P4M0|=gpio_pin;
                P4M1&=~mode;
            }break;
            case GPIO_OUT_HR:
            {
                P4M0&=~gpio_pin;
                P4M1|=mode;
            }break;
            case GPIO_OUT_OD:
            {
                P4M0|=gpio_pin;
                P4M1|=mode;
            }break;
        }
    }
    else if(port==GPIO_P5)
    {
        switch(mode)
        {
            case GPIO_OUT_LP:
            {
                P5M0&=~gpio_pin;
                P5M1&=~mode;
            }break;
            case GPIO_OUT_PP:
            {
                P5M0|=gpio_pin;
                P5M1&=~mode;
            }break;
            case GPIO_OUT_HR:
            {
                P5M0&=~gpio_pin;
                P5M1|=mode;
            }break;
            case GPIO_OUT_OD:
            {
                P5M0|=gpio_pin;
                P5M1|=mode;
            }break;
        }
    }


}

//===================================
//函数名        :usart_init
//函数功能      :初始化串口
//输入          :串口号 ,波特率
//输出          :
//===================================
bit usart_init(USARTn_e usartn,uint32 baud )
{
    if(usartn==USART1)
    {
        PCON &= 0x7F;		//波特率不倍速
    	SCON = 0x50;		//8位数据,可变波特率
    	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
    	BRT  =256-(FOSC/(32*baud));		    //设定独立波特率发生器重装值
    	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
    	AUXR |= 0x10;		//启动独立波特率发生器
        return 1;
    }
    else if(usartn==USART2)
    {
        AUXR &= 0xF7;		//波特率不倍速
    	S2CON = 0x50;		//8位数据,可变波特率
    	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
    	BRT = 256-(FOSC/(32*baud));		//设定独立波特率发生器重装值
    	AUXR |= 0x10;		//启动独立波特率发生器
        return 1;
    }
    else
        return 0;
}

//===================================
//函数名        :putchar
//函数功能      :
//输入          :
//输出          :
//==================================
char putchar(char c)
{
    usart_send(printf_usart,c);
    return c;
}


//===================================
//函数名        :usart_send
//函数功能      :串口发送数据
//输入          :串口号 ,数据
//输出          :
//===================================
bit usart_send(USARTn_e usartn,uint8 Data)
{
    if(usartn==USART1)
    {
        SBUF=Data;
        while(!TI);
        TI=0;
        return 1;
    }
    else if(usartn==USART2)
    {
        S2BUF=Data;
        while(!(S2CON&0x20));
        S2CON&=0xfd;
        return 1;
    }
    else
        return 0;
}
//===================================
//函数名        :usart_get
//函数功能      :串口接收数据,查询方式
//输入          :串口号 
//输出          :数据
//===================================
uint8 usart_get(USARTn_e usartn)
{
    uint8 d;
    if(usartn==USART1)
    {
        if(RI)
        {
            d=SBUF;
            RI=0;
        }   
    }
    else if(usartn==USART2)
    {
        if(S2CON&0x01)
        {
            d=S2BUF;
            S2CON&=0xfe;
        }
    }
    return d;
}
//===================================
//函数名        :usart_putbuff
//函数功能      :发送len个字节BUFF
//输入          :串口号 ,数组地址,数组长度
//输出          :
//===================================
void usart_putbuff(USARTn_e usartn,uint8 *buff,uint32 len)
{
    while(len--)
    {
        usart_send(usartn, *buff);
        buff++;
    }
}
//===================================
//函数名        :usart_putstr
//函数功能      :发送字符串
//输入          :串口号 ,字符串
//输出          :
//===================================
void usart_putstr(USARTn_e usartn,uint8 *str)
{
    while(*str)
    {
        usart_send(usartn, *str++);
    }
}
//===================================
//函数名        :usart_sware
//函数功能      :虚拟示波器
//输入          :串口号 ,数据地址,数据长度
//输出          :
//===================================
void usart_sware(USARTn_e usartn,void *wareaddr,uint32 waresize)
{
    uint8 cmdf[2]={0x03, 0xfc};   //前指令  
    uint8 cmdr[2]={0xfc, 0x03};   //后指令      
    
    
    usart_putbuff(usartn,cmdf,sizeof(cmdf));
    usart_putbuff(usartn,(uint8 *)(wareaddr),waresize);
    usart_putbuff(usartn,cmdr,sizeof(cmdr));
}


//===================================
//函数名        :adc_init
//函数功能      :
//输入          :
//输出          :
//===================================
void adc_init(ADC_ch adc_ch,ADC_CMD cmd)
{
    uint16 x=0,n=2;
    P1ASF|=adc_ch;
    ADC_RES=0;
    ADC_RESL=0;
    ADC_CONTR = ADC_POWER|cmd ;
    
    while (n--)
    {
        x = 5000;
        while (x--);
    }   

    //AUXR1|=0x04;        //高二位在ADC_RES中


}
//===================================
//函数名        :adc_get        
//函数功能      :
//输入          :
//输出          :
//===================================
uint16 adc_get(ADC_ch adc_ch,ADC_CMD cmd)
{
    
    ADC_CONTR=ADC_POWER | adc_ch | ADC_START| cmd;
    
    _nop_();                        //Must wait before inquiry
    _nop_();
    _nop_();
    _nop_();

    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
    return (ADC_RES+ADC_RESL);
        
   
}
//===================================
//函数名        :pwm_init_NT0        
//函数功能      :
//输入          :PCA模块,不使用T0产生时钟,时钟分频系数0,2,4,6,8,12
//输出          :
//===================================
void pwm_init_NT0(PCA_n pca,uint8 div)
{
    CCON = 0;                       //Initial PCA control register
                                    //PCA timer stop running
                                    //Clear CF flag
                                    //Clear all module interrupt flag
    CL = 0;                         //Reset PCA base timer
    CH = 0;
    switch(div)
    {
        case 0:CMOD=0x08;break;
        case 2:CMOD=0x02;break;
        case 4:CMOD=0x05;break;
        case 6:CMOD=0x06;break;
        case 8:CMOD=0x07;break;
        case 12:CMOD=0x00;break;
    }
    switch(pca)
    {
        case PCA_0:CCAPM0=0x42;                    //PCA module-0 work in 8-bit PWM mode and no PCA interrupt
        break;
        case PCA_1:CCAPM1=0x42;                    //PCA module-1 work in 8-bit PWM mode and no PCA interrupt
        break;
    }

    CR = 1;                         //PCA timer start run


}
//===================================
//函数名        :pwm_init_T0        
//函数功能      :
//输入          :PCA模块,使用T0产生时钟
//输出          :
//===================================
void pwm_init_T0(PCA_n pca,uint32 freq)
{
   TMOD=0x02;
   CMOD=0X04;           //选择T0溢出率为时钟
   if(freq>1000)
   {
       AUXR=0x80;           //T0工作在1T模式下
       TH0=TL0=256-(uint8)(FOSC/freq/256);
   }
   else
   {
        AUXR&=0x7f;         //T0工作在12T模式下
        TH0=TL0=256-(uint8)(FOSC/freq/256/12);
   }
   CCON = 0;                       //Initial PCA control register
                                    //PCA timer stop running
                                    //Clear CF flag
                                    //Clear all module interrupt flag
   CL = 0;                         //Reset PCA base timer
   CH = 0;
   switch(pca)
   {
       case PCA_0:CCAPM0=0x42;                    //PCA module-0 work in 8-bit PWM mode and no PCA interrupt
       break;
       case PCA_1:CCAPM1=0x42;                    //PCA module-1 work in 8-bit PWM mode and no PCA interrupt
       break;
   }

    CR = 1;                         //PCA timer start run
    TR0=1;                          //启动T0定时器 
}













//===================================
//函数名        :pwm_duty        
//函数功能      :
//输入          :
//输出          :
//===================================
void pwm_duty(PCA_n pca,uint8 duty)
{
    switch(pca)
    {
        case PCA_0: CCAP0H = CCAP0L = 256-duty;
        break;
        case PCA_1: CCAP1H = CCAP1L = 256-duty;
        break;
    }
}

//===================================
//函数名        :pwm_perc        
//函数功能      :输入百分比占空比
//输入          :
//输出          :
//===================================
void pwm_perc(PCA_n pca,uint8 perc)
{
   
   switch(pca)
    {
        case PCA_0: CCAP0H = CCAP0L = (uint8)((100-perc)*2.56);
        break;
        case PCA_1: CCAP1H = CCAP1L = (uint8)((100-perc)*2.56);
        break;
    } 
}
//===================================
//函数名        :servo        
//函数功能      :输入目标角度
//输入          :
//输出          :
//===================================
//void servo(PCA_n pca,uint8 ang)
//{
//	pwm_duty(pca,((ang/9)+5)*128);
//}































