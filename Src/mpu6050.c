#include "mpu6050.h"


/* IICд1Byte */
uint8_t MPU6050_Write_Byte(uint8_t reg, uint8_t data)
{
	IIC_Start();
	IIC_Send_Byte((MPU6050_ADDR << 1) | 0);		//����������ַ + дָ��0
	if(IIC_Wait_Ack())
		return 1;

	IIC_Send_Byte(reg);		//д�Ĵ�����ַ
	IIC_Wait_Ack();
	IIC_Send_Byte(data);
	if(IIC_Wait_Ack())
		return 1;
	IIC_Stop();
	return 0;
}

/* IIC������ȡ */
uint8_t MPU6050_Read_Len(uint8_t addr, uint16_t reg, uint8_t len, uint8_t *buf)
{
	IIC_Start();
	IIC_Send_Byte((addr << 1) | 1);		//����������ַ + дָ��0
	if(IIC_Wait_Ack())
	{
		printf("�ӻ���Ӧ��\r\n");
		return 1;
	}
//	printf("Ack OK1\r\n");
	
	IIC_Send_Byte(reg & 0x00ff);		//д�Ĵ�����ַ
//printf("1\r\n");
	IIC_Wait_Ack();				//�ȴ�Ӧ��
	
	IIC_Send_Byte((reg & 0xff00) >> 8);		//д�Ĵ�����ַ
//printf("2\r\n");
	IIC_Wait_Ack();				//�ȴ�Ӧ��
	
//	IIC_Start();
//	IIC_Send_Byte(addr << 1 | 0x01);	//����������ַ + ��ָ��1
//	IIC_Wait_Ack();				//�ȴ�Ӧ��
//	if(IIC_Wait_Ack())
//	{
////		printf("�ӻ���Ӧ��2\r\n");
//		return 1;
//	}
//	printf("Ack OK2\r\n");
//	while(len)
//	{
//		if(len ==1)
//			*buf = IIC_Read_Byte(0);	//�����һ���ֽ�ʱ��Ҫ�ظ���Ӧ���źţ���������ֹ�ź��Խ�����������PPT�н��ú���ϸ�淶https://wenku.baidu.com/view/bdb46aa60029bd64783e2c6f.html
//		else
uint8_t value = 0;
			value = IIC_Read_Byte(1);	//���Ƕ����һ���ֽ�ҪӦ��
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


/* IICд */
uint8_t MPU6050_Write_Len(uint8_t addr, uint16_t reg, uint8_t len, uint16_t value)
{
	IIC_Start();
	IIC_Send_Byte((addr << 1) | 0);		//����������ַ + дָ��0
	if(IIC_Wait_Ack())
	{
		printf("�ӻ���Ӧ��\r\n");
		return 1;
	}
//	printf("Ack OK1\r\n");
	
	IIC_Send_Byte(reg & 0x00ff);		//д�Ĵ�����ַ
//printf("1\r\n");
	IIC_Wait_Ack();				//�ȴ�Ӧ��
	
	IIC_Send_Byte((reg & 0xff00) >> 8);		//д�Ĵ�����ַ
//printf("2\r\n");
	IIC_Wait_Ack();				//�ȴ�Ӧ��
	
		IIC_Send_Byte(value & 0x00ff);		//д�Ĵ�����ַ
//printf("2\r\n");
	IIC_Wait_Ack();				//�ȴ�Ӧ��
	
		IIC_Send_Byte((value & 0xff00) >> 8);		//д�Ĵ�����ַ
//printf("2\r\n");
	IIC_Wait_Ack();				//�ȴ�Ӧ��
	
//	IIC_Start();
//	IIC_Send_Byte(addr << 1 | 0x01);	//����������ַ + ��ָ��1
//	IIC_Wait_Ack();				//�ȴ�Ӧ��
//	if(IIC_Wait_Ack())
//	{
////		printf("�ӻ���Ӧ��2\r\n");
//		return 1;
//	}
//	printf("Ack OK2\r\n");
//	while(len)
//	{
//		if(len ==1)
//			*buf = IIC_Read_Byte(0);	//�����һ���ֽ�ʱ��Ҫ�ظ���Ӧ���źţ���������ֹ�ź��Խ�����������PPT�н��ú���ϸ�淶https://wenku.baidu.com/view/bdb46aa60029bd64783e2c6f.html
//		else
//uint8_t value = 0;
//			value = IIC_Read_Byte(1);	//���Ƕ����һ���ֽ�ҪӦ��
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
