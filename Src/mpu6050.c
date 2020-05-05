#include "mpu6050.h"


/* IIC写1Byte */
uint8_t MPU6050_Write_Byte(uint8_t reg, uint8_t data)
{
	IIC_Start();
	IIC_Send_Byte((MPU6050_ADDR << 1) | 0);		//发送器件地址 + 写指令0
	if(IIC_Wait_Ack())
		return 1;

	IIC_Send_Byte(reg);		//写寄存器地址
	IIC_Wait_Ack();
	IIC_Send_Byte(data);
	if(IIC_Wait_Ack())
		return 1;
	IIC_Stop();
	return 0;
}

/* IIC连续读取 */
uint8_t MPU6050_Read_Len(uint8_t addr, uint16_t reg, uint8_t len, uint8_t *buf)
{
	IIC_Start();
	IIC_Send_Byte((addr << 1) | 1);		//发送器件地址 + 写指令0
	if(IIC_Wait_Ack())
	{
		printf("从机无应答\r\n");
		return 1;
	}
//	printf("Ack OK1\r\n");
	
	IIC_Send_Byte(reg & 0x00ff);		//写寄存器地址
//printf("1\r\n");
	IIC_Wait_Ack();				//等待应答
	
	IIC_Send_Byte((reg & 0xff00) >> 8);		//写寄存器地址
//printf("2\r\n");
	IIC_Wait_Ack();				//等待应答
	
//	IIC_Start();
//	IIC_Send_Byte(addr << 1 | 0x01);	//发送器件地址 + 读指令1
//	IIC_Wait_Ack();				//等待应答
//	if(IIC_Wait_Ack())
//	{
////		printf("从机无应答2\r\n");
//		return 1;
//	}
//	printf("Ack OK2\r\n");
//	while(len)
//	{
//		if(len ==1)
//			*buf = IIC_Read_Byte(0);	//读最后一个字节时，要回复非应答信号，并发出终止信号以结束读操作，PPT中讲得很详细规范https://wenku.baidu.com/view/bdb46aa60029bd64783e2c6f.html
//		else
uint8_t value = 0;
			value = IIC_Read_Byte(1);	//不是读最后一个字节要应答
//			printf("0x%x\r\n", value);
uint8_t value2 = 0;
			value2 = IIC_Read_Byte(0);
			printf("read reg = 0x%04X value = 0x%02X", reg, value2);
			printf("%02X\r\n", value);
//		len--;
//		buf++;
//	}
	IIC_Stop();
	return 0;
}


/* IIC写 */
uint8_t MPU6050_Write_Len(uint8_t addr, uint16_t reg, uint8_t len, uint16_t value)
{
	IIC_Start();
	IIC_Send_Byte((addr << 1) | 0);		//发送器件地址 + 写指令0
	if(IIC_Wait_Ack())
	{
		printf("从机无应答\r\n");
		return 1;
	}
//	printf("Ack OK1\r\n");
	
	IIC_Send_Byte(reg & 0x00ff);		//写寄存器地址
//printf("1\r\n");
	IIC_Wait_Ack();				//等待应答
	
	IIC_Send_Byte((reg & 0xff00) >> 8);		//写寄存器地址
//printf("2\r\n");
	IIC_Wait_Ack();				//等待应答
	
		IIC_Send_Byte(value & 0x00ff);		//写寄存器地址
//printf("2\r\n");
	IIC_Wait_Ack();				//等待应答
	
		IIC_Send_Byte((value & 0xff00) >> 8);		//写寄存器地址
//printf("2\r\n");
	IIC_Wait_Ack();				//等待应答
	
//	IIC_Start();
//	IIC_Send_Byte(addr << 1 | 0x01);	//发送器件地址 + 读指令1
//	IIC_Wait_Ack();				//等待应答
//	if(IIC_Wait_Ack())
//	{
////		printf("从机无应答2\r\n");
//		return 1;
//	}
//	printf("Ack OK2\r\n");
//	while(len)
//	{
//		if(len ==1)
//			*buf = IIC_Read_Byte(0);	//读最后一个字节时，要回复非应答信号，并发出终止信号以结束读操作，PPT中讲得很详细规范https://wenku.baidu.com/view/bdb46aa60029bd64783e2c6f.html
//		else
//uint8_t value = 0;
//			value = IIC_Read_Byte(1);	//不是读最后一个字节要应答
//			printf("0x%x\r\n", value);
//uint8_t value2 = 0;
//			value2 = IIC_Read_Byte(0);
//			printf("0x%x\r\n", value);
//			printf("0x%x\r\n", value2);
//		len--;
//		buf++;
//	}
	IIC_Stop();
printf("write reg = 0x%04X value = 0x%04X\r\n", reg, value);
	return 0;
}
