#include "iic_2_phy.h"


/* IIC写1Byte */
uint8_t Pyh_Write_Byte(uint8_t reg, uint8_t data)
{
	IIC_Start_2();
	IIC_Send_Byte_2((PHY_IIC_ADDR << 1) | 0);		//发送器件地址 + 写指令0
	if(IIC_Wait_Ack_2())
		return 1;

	IIC_Send_Byte_2(reg);		//写寄存器地址
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(data);
	if(IIC_Wait_Ack_2())
		return 1;
	IIC_Stop_2();
	return 0;
}






/* IIC写1Byte */
uint8_t PHY_Write_Byte(uint8_t reg, uint8_t data)
{
	IIC_Start_2();
	IIC_Send_Byte_2((PHY_IIC_ADDR << 1) | 0);		//发送器件地址 + 写指令0
	if(IIC_Wait_Ack_2())
		return 1;

	IIC_Send_Byte_2(reg);		//写寄存器地址
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(data);
	if(IIC_Wait_Ack_2())
		return 1;
	IIC_Stop_2();
	return 0;
}

/* IIC连续读取 */
uint8_t PHY_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	IIC_Start_2();
	IIC_Send_Byte_2((addr << 1) | 0);		//发送器件地址 + 写指令0
	if(IIC_Wait_Ack_2())
	{
		printf("从机无应答\r\n");
		return 1;
	}
//	printf("Ack OK1\r\n");
	
	IIC_Send_Byte_2(reg);		//写寄存器地址
	IIC_Wait_Ack_2();				//等待应答
	IIC_Start_2();
	IIC_Send_Byte_2(addr << 1 | 0x01);	//发送器件地址 + 读指令1
	IIC_Wait_Ack_2();				//等待应答
//	if(IIC_Wait_Ack_2())
//	{
////		printf("从机无应答2\r\n");
//		return 1;
//	}
//	printf("Ack OK2\r\n");
	uint8_t value = 0;
	while(len)
	{
		if(len ==1)
			value = IIC_Read_Byte_2(0);	//读最后一个字节时，要回复非应答信号，并发出终止信号以结束读操作，PPT中讲得很详细规范https://wenku.baidu.com/view/bdb46aa60029bd64783e2c6f.html
		else
			value = IIC_Read_Byte_2(1);	//不是读最后一个字节要应答
		len--;
		buf++;
	}
	IIC_Stop_2();
	printf("read reg = 0x%02X value = 0x%02X\r\n", reg, value);
	return 0;
}

