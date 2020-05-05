#include "iic_2.h"

/* ����IIC��ʼ�ź� */
void IIC_Start_2(void)
{
	SCL_2_L;
	SDA_2_OUT();	//SDA��Ϊ��������ɺ�ϰ�ߣ����ݱ仯֮ǰ��һ������ʱ����
	SDA_2_H;
	SCL_2_H;
	IIC_Delay_2();
	SDA_2_L;				//START:when CLK is high,DATA change form high to low 
	IIC_Delay_2();
	SCL_2_L;				//ǯסI2C���ߣ�׼�����ͻ�������� 
}

/* ����IICֹͣ�ź� */
void IIC_Stop_2(void)
{
	SCL_2_L;
	SDA_2_OUT();	//SDA��Ϊ���
	SDA_2_L;
	SCL_2_H;
	IIC_Delay_2();
	SDA_2_H;			//STOP:when CLK is high DATA change form low to high
	IIC_Delay_2();
}

/* �������ظ�Ӧ���ź�0(ACK) */
void IIC_Ack_2(void)
{
	SCL_2_L;
	SDA_2_OUT();
	SDA_2_L;				//������Ϊ�͵�ƽ,20171211 2:53,�㵽��ô���ԭ�������ҵ��ˣ������߸ı�֮ǰһ��Ҫ��ʱ�������ͣ���Ȼ���͵Ĳ�����ʼ�źž���ֹͣ�ź�
	IIC_Delay_2();
	SCL_2_H;
	IIC_Delay_2();
	SCL_2_L;				//��һ��ʱ���»ظ�0
}

/* �������ظ�Ӧ���ź�1(NACK) Ҳ�в�Ӧ��*/
void IIC_NAck_2(void)
{
	SCL_2_L;
	SDA_2_OUT();
	SDA_2_H;				//������Ϊ�ߵ�ƽ,20171211 2:53,�㵽��ô���ԭ�������ҵ��ˣ������߸ı�֮ǰһ��Ҫ��ʱ�������ͣ���Ȼ���͵Ĳ�����ʼ�źž���ֹͣ�ź�
	IIC_Delay_2();
	SCL_2_H;
	IIC_Delay_2();
	SCL_2_L;				//��һ��ʱ���»ظ�1
}

/* �ȴ�Ӧ���ź� */
uint8_t IIC_Wait_Ack_2(void)
{
	uint8_t time = 0;
	SDA_2_IN();
	SDA_2_H;
	IIC_Delay_2();
	SCL_2_H;
	IIC_Delay_2();
	while(READ_SDA_2)
	{
		time++;
		if(time > 250)
		{
			IIC_Stop_2();
			printf("no ack 22222\r\n");
			return 1;		//��Ӧ���źţ�ֹͣIIC������1
		}
		
	}
//	printf("ack 33333\r\n");
	SCL_2_L;
	return 0;				//��Ӧ���źţ�����0
}

/* ��������1Byte */
void IIC_Send_Byte_2(uint8_t txd)
{
	SDA_2_OUT();
	SCL_2_L;	//����ʱ�ӿ�ʼ���ݴ��䣬��ʵ����һ���Ѿ�Ϊ����
	for(int i = 0; i < 8; i++)
	{
		if((txd & 0x80))
			SDA_2_H;
		else
			SDA_2_L;
		SCL_2_H;
		IIC_Delay_2();
		SCL_2_L;
		IIC_Delay_2();
		txd <<= 1;
	}
}

/* �����Ӵӻ���ȡ1Byte 0����Ӧ��ӻ� 1��Ӧ��ӻ� */
uint8_t IIC_Read_Byte_2(uint8_t ack)
{
	uint8_t receive = 0;
	SDA_2_IN();
	for(int i = 0; i < 8; i++)
	{
		SCL_2_L;
		IIC_Delay_2();
		SCL_2_H;
		receive <<= 1;
		if(READ_SDA_2)
		{
//			printf("01 \r\n");
			receive |= 0x01;
		}
		else
		{
//			printf("00 \r\n");
		}
		IIC_Delay_2();	
	}
//		printf("receive = %x\r\n", receive);
	if(ack == 0)
		IIC_NAck_2();		//��Ӧ��
	else
		IIC_Ack_2();		//Ӧ��
	return receive;
}

/* IIC��ʱ */
void IIC_Delay_2(void)
{
//	Delay_us_2(4);
	__NOP();	//12Mʱ��������ÿ��NOP��ʱ1us,72Mʱ����������ʱ1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
//	
		__NOP();	//12Mʱ��������ÿ��NOP��ʱ1us,72Mʱ����������ʱ1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
		__NOP();	//12Mʱ��������ÿ��NOP��ʱ1us,72Mʱ����������ʱ1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
		__NOP();	//12Mʱ��������ÿ��NOP��ʱ1us,72Mʱ����������ʱ1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
//	
//		__NOP();	//12Mʱ��������ÿ��NOP��ʱ1us,72Mʱ����������ʱ1/6us
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();

}

/* ��ʱ����us */
void Delay_us_2(unsigned long CountLing)
{
//    signed char i;
    while(CountLing--)
    {
//        i = 10;
//        while(i--);
//			__NOP();	//12Mʱ��������ÿ��NOP��ʱ1us,72Mʱ����������ʱ1/6us
//			__NOP();
//			__NOP();
//			__NOP();
//			__NOP();
//			__NOP();
    }
}

