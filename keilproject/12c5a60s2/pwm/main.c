#include "common.h"
#include "lib.h"
int main()
{
    usart_init(USART1,115200);
    pwm_init_T0(PCA_0,50);
    adc_init(ADC_4,ADC_SPEEDHH);
    while(1)
    {
//       printf("当前ADC_4通道值：%d\n",adc_get(ADC_4,ADC_SPEEDHH)); 
//       delay_ms(500);
//        uint16 adc=2000;
//        adc=adc_get(ADC_4,ADC_SPEEDHH);
//        usart_sware(USART1,&adc,sizeof(adc)); 
		pwm_perc(PCA_0,90);
    }
}


