#include<reg52.h>
#ifndef _EEPROM_H
#define _EEPROM_H
#include<intrins.h>

extern unsigned char R[20];			//环境参数

/**********************************************
			定义ISP/IAP操作命令
***********************************************/
#define EECMD_read 	0x01		//读
#define EECMD_write	0x02		//写
#define EECMD_erase	0x03		//扇区擦除

#define EE_Waittime	0x01		//定义CPU等待时间
/**********************************************
			寄存器声明
***********************************************/
sfr ISP_DATA=0xe2;
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
/**********************************************
				功能函数
***********************************************/
void ISP_IAP_enable(void);		//打开ISP/IAP功能
void ISP_IAP_disable(void);		//关闭ISP/IAP功能
void ISP_IAP_trig(void);		//公共触发
unsigned char EEPROM_Read(unsigned int addr);	//读取指定地址里的值
void EEPROM_Write(unsigned int addr,unsigned char dat);	//向指定地址写入字节
void EEPROM_Erase(unsigned int sector_addr);	//扇区擦除
void EEPROM_Memory(void);

#endif