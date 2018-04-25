#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include "common.h"
//==========================================
//不同单片机包含不同的头文件
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/


#if STC12

#include "stc12c5a60s2.h"
#include "lib.h"
#define FOSC 11059200
#define BUAD 115200
#elif   STM32

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#define FOSC 72000000
#endif 


#ifdef RTE_DEVICE_STDPERIPH_ADC
#include "adc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_BKP
#include "bkp.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_DAC
#include "dac.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_DMA
#include "dma.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_EXTI
#include "exti.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_FLASH
#include "flash.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_FSMC
#include "fsmc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_GPIO
#include "gpio.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_I2C
#include "i2c.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_IWDG
#include "iwdg.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_PWR
#include "pwr.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_RTC
#include "rtc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_SDIO
#include "sdio.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_SPI
#include "spi.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_TIM
#include "tim.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_USART
#include "usart.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_WWDG
#include "wwdg.h"
#endif
#ifdef RTE_DEVICE_STDPERIPH_FRAMEWORK
#include "nvic.h" 
#endif



#endif



