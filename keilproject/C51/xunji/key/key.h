#ifndef _KEY_H
#define _KEY_H
#include <STC12C5A60S2.h>
#include "pwm.h"

sbit KEY_U=P3^3;
sbit KEY_D=P3^2;
sbit KEY_O=P3^4;

extern char Keyflag;

void SpeedKeyScan(void);






#endif 