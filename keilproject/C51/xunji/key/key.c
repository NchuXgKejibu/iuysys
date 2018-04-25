#include "key.h"


char Keyfalg=1;

void SpeedKeyScan(void)
{
    if(KEY_U==0)
    {
        delay_ms(10);
        if(KEY_U==0)
        {
            MOTORSpeed+=10;
            if(MOTORSpeed>100)
                MOTORSpeed=100;
        }
    }
    if(KEY_D==0)
    {
        delay_ms(10);
        if(KEY_D==0)
        {
            MOTORSpeed-=10;
            if(MOTORSpeed<0)
                MOTORSpeed=0;
        }
    }
    if(KEY_O==0)
    {
        delay_ms(10);
        if(KEY_O==0)
        {
            Keyflag=0;
            TR0=1;                
        }
    }
    MOTOR(MOTORSpeed);
}

