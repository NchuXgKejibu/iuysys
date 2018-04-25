#include <STC12C5A60S2.h>
#include <intrins.h>
#include "PWM.h"
#include "key.h"



int main()
{
    PWM_Init();
    
    while(Keyflag)
    {
        SpeedKeyScan();
        MOTOR(MOTORSpeed);    
    }
    
     
}

/***************************************************/
void PWM_interrupt(void) interrupt 5
{
	TF2=0;
	MOTORCount++;
    Angle=(~P2)&0x7e;
	MOTORCount=MOTORCount>50?1:MOTORCount;
    if(MOTORCount<speed/2)
		PWM0=1;
	else
		PWM0=0;	
}
/***************************************************/
/***************************************************/
void Servo_interrupt(void) interrupt 1
{
    TH0=0xff;			//
	TL0=0xa4;
    ServoCount++; 
    ServoCount=ServoCount>200?1:ServoCount;
    if(ServoCount<(ServoAngle/9)+5)  
		Servo0=1;
	else
		Servo0=0;	
}

/***************************************************/