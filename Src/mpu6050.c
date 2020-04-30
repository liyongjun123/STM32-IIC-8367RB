#include "mpu6050.h"

/* 初始化MPU6050 */
uint8_t MPU6050_Init(void)
{
	MPU6050_Write_Byte(MPU_PWR_MGMT1_REG, 0x80);	//重启
	HAL_Delay(100);
	MPU6050_Write_Byte(MPU_PWR_MGMT1_REG, 0x00);	//唤醒
//	MPU6050_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
//	MPU6050_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
//	MPU6050_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
//	MPU6050_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
//	uint16_t rate = 50;
//	uint8_t data;
//	if(rate>1000)rate=1000;
//	if(rate<4)rate=4;
//	data=1000/rate-1;
//	data=MPU6050_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
// 	uint16_t lpf = 25;
//	data=0;
//	if(lpf>=188)data=1;
//	else if(lpf>=98)data=2;
//	else if(lpf>=42)data=3;
//	else if(lpf>=20)data=4;
//	else if(lpf>=10)data=5;
//	else data=6; 
//	return MPU6050_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器 
	
}

/* 读取温度 */
uint16_t MPU6050_Read_Temperature(void)
{
	uint8_t buf[2];
	int16_t raw;		//为什么是int16_t呢，是因为手册中有说到：TEMP_OUT 16为有符号数值
	float temp;
	MPU6050_Read_Len(MPU6050_ADDR, 0xC0, 2, buf);
	raw = buf[0] << 8 | buf[1];
//	printf("raw = 0x%x\r\n", raw);
	temp = 36.53 + (double)raw / 340;
	printf("temp = %f\r\n", temp);
	
	
//	int16_t f = -32767;
////	f = 0x80 << 8;
//	printf("f = 0x%x\r\n", f);
//	printf("sizeof(f) = %d\r\n", sizeof(f));
//	printf("f = %d\r\n", f);
}

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
