#include "iic_2_phy.h"


/* IICд1Byte */
uint8_t Pyh_Write_Byte(uint8_t reg, uint8_t data)
{
	IIC_Start_2();
	IIC_Send_Byte_2((PHY_IIC_ADDR << 1) | 0);		//����������ַ + дָ��0
	if(IIC_Wait_Ack_2())
		return 1;

	IIC_Send_Byte_2(reg);		//д�Ĵ�����ַ
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(data);
	if(IIC_Wait_Ack_2())
		return 1;
	IIC_Stop_2();
	return 0;
}






/* IICд1Byte */
uint8_t PHY_Write_Byte(uint8_t reg, uint8_t data)
{
	IIC_Start_2();
	IIC_Send_Byte_2((PHY_IIC_ADDR << 1) | 0);		//����������ַ + дָ��0
	if(IIC_Wait_Ack_2())
		return 1;

	IIC_Send_Byte_2(reg);		//д�Ĵ�����ַ
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(data);
	if(IIC_Wait_Ack_2())
		return 1;
	IIC_Stop_2();
	return 0;
}

/* IIC������ȡ */
uint8_t PHY_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	IIC_Start_2();
	IIC_Send_Byte_2((addr << 1) | 0);		//����������ַ + дָ��0
	if(IIC_Wait_Ack_2())
	{
		printf("�ӻ���Ӧ��\r\n");
		return 1;
	}
//	printf("Ack OK1\r\n");
	
	IIC_Send_Byte_2(reg);		//д�Ĵ�����ַ
	IIC_Wait_Ack_2();				//�ȴ�Ӧ��
	IIC_Start_2();
	IIC_Send_Byte_2(addr << 1 | 0x01);	//����������ַ + ��ָ��1
	IIC_Wait_Ack_2();				//�ȴ�Ӧ��
//	if(IIC_Wait_Ack_2())
//	{
////		printf("�ӻ���Ӧ��2\r\n");
//		return 1;
//	}
//	printf("Ack OK2\r\n");
	uint8_t value = 0;
	while(len)
	{
		if(len ==1)
			value = IIC_Read_Byte_2(0);	//�����һ���ֽ�ʱ��Ҫ�ظ���Ӧ���źţ���������ֹ�ź��Խ�����������PPT�н��ú���ϸ�淶https://wenku.baidu.com/view/bdb46aa60029bd64783e2c6f.html
		else
			value = IIC_Read_Byte_2(1);	//���Ƕ����һ���ֽ�ҪӦ��
		len--;
		buf++;
	}
	IIC_Stop_2();
	printf("read reg = 0x%02X value = 0x%02X\r\n", reg, value);
	return 0;
}

