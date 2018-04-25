#include"EEPROM.h"

unsigned char R[20]={0};		//环境参数


void ISP_IAP_enable(void)
{
	EA=0;							//关中断
	ISP_CONTR&=0x18;				//清除低三位
	ISP_CONTR|=EE_Waittime;			//写入硬件延时
	ISP_CONTR|=0x80;				//ISPEN使能
}

void ISP_IAP_disable(void)
{
	ISP_CONTR&=0x7f;				//ISPEN=0;
	ISP_TRIG=0x00;
	EA=1;							//开中断
}

void ISP_IAP_trig(void)
{
	ISP_IAP_enable();				//打开ISP/IAP
	ISP_TRIG=0x46;					//触发命令1
	ISP_TRIG=0xb9;					//触发命令2
	_nop_();
}

unsigned char EEPROM_Read(unsigned int addr)
{
	ISP_ADDRH=(unsigned char)(addr>>8);			//地址
	ISP_ADDRL=(unsigned char)(addr&0x00ff);
	ISP_CMD&=0xf8;								//清除低三位
	ISP_CMD|=EECMD_read;						//写入读命令
	ISP_IAP_trig();								//触发
	return(ISP_DATA);							//返回数据
}

void EEPROM_Write(unsigned int addr,unsigned char dat)
{
	ISP_ADDRH=(unsigned char)(addr>>8);			//地址
	ISP_ADDRL=(unsigned char)(addr&0x00ff);
	ISP_CMD&=0xf8;								//清除低三位
	ISP_CMD|=EECMD_write;					//写入写命令
	ISP_DATA=dat;								//写入数据
	ISP_IAP_trig();								//触发
	ISP_IAP_disable();							//关闭ISP/IAP
}

void EEPROM_Erase(unsigned int sector_addr)
{
	unsigned int sectoraddr;
	sectoraddr=sector_addr&0xfe00;				//取扇区地址
	ISP_ADDRH=(unsigned char)(sectoraddr>>8);	//地址
	ISP_ADDRL=0x00;
	ISP_CMD&=0xf8;								//清除低三位
	ISP_CMD|=EECMD_erase;						//写入擦除命令
	ISP_IAP_trig();								//触发
	ISP_IAP_disable();							//关闭ISP/IAP
}

void EEPROM_Memory(void)
{
	int turn;
	for(turn=0;turn<20;turn++)
	{
		R[turn]=EEPROM_Read(0x2000+turn);	
	}
}


















