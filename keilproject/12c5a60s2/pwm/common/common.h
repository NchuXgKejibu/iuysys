#ifndef __COMMON_H__
#define __COMMON_H__

//选择单片机
#define STC12 1
//#define STM32   1
//==========================================
//不同单片机包含不同的头文件
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/


#if STC12

#include "stc12c5a60s2.h"

#elif   STM32

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#endif   


/*
 * 数据类型声明
 */
typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned int        uint16; /* 16 bits */
typedef unsigned long       uint32; /* 32 bits */

typedef char                int8;   /*  8 bits */
typedef int                 int16;  /* 16 bits */
typedef long                int32;  /* 32 bits */

/*
 * 求最大值和最小值
 */
#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )


/*
 * 返回数组元素的个数
 */
#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )

/*
 * 宏定义实现返回绝对值（x里不能有自加自减的语句，否则变量出错）
 */
#define ABS(x) (((x) > 0) ? (x) : (-(x)))

/*
 * 获取结构体某成员偏移
 */
#define OFFSET(type, member)    (uint32)(&(((type *)0)->member))

/*
 * 确保x的范围为 min~max
 */
#define RANGE(x,max,min)        ((uint8)((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))



#endif
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
extern void delay_us(uint32 i);        //延时函数，延时us

extern void delay_ms(uint32 i);        //延时函数，延时ms
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
















