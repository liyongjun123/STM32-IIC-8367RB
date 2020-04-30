#include "IIC.h"

/* ����IIC��ʼ�ź� */
void IIC_Start(void)
{
	SCL_L;
	SDA_OUT();	//SDA��Ϊ��������ɺ�ϰ�ߣ����ݱ仯֮ǰ��һ������ʱ����
	SDA_H;
	SCL_H;
	IIC_Delay();
	SDA_L;				//START:when CLK is high,DATA change form high to low 
	IIC_Delay();
	SCL_L;				//ǯסI2C���ߣ�׼�����ͻ�������� 
}

/* ����IICֹͣ�ź� */
void IIC_Stop(void)
{
	SCL_L;
	SDA_OUT();	//SDA��Ϊ���
	SDA_L;
	SCL_H;
	IIC_Delay();
	SDA_H;			//STOP:when CLK is high DATA change form low to high
	IIC_Delay();
}

/* �������ظ�Ӧ���ź�0(ACK) */
void IIC_Ack(void)
{
	SCL_L;
	SDA_OUT();
	SDA_L;				//������Ϊ�͵�ƽ,20171211 2:53,�㵽��ô���ԭ�������ҵ��ˣ������߸ı�֮ǰһ��Ҫ��ʱ�������ͣ���Ȼ���͵Ĳ�����ʼ�źž���ֹͣ�ź�
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L;				//��һ��ʱ���»ظ�0
}

/* �������ظ�Ӧ���ź�1(NACK) Ҳ�в�Ӧ��*/
void IIC_NAck(void)
{
	SCL_L;
	SDA_OUT();
	SDA_H;				//������Ϊ�ߵ�ƽ,20171211 2:53,�㵽��ô���ԭ�������ҵ��ˣ������߸ı�֮ǰһ��Ҫ��ʱ�������ͣ���Ȼ���͵Ĳ�����ʼ�źž���ֹͣ�ź�
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L;				//��һ��ʱ���»ظ�1
}

/* �ȴ�Ӧ���ź� */
uint8_t IIC_Wait_Ack(void)
{
	uint8_t time = 0;
	SDA_IN();
	SDA_H;
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	while(READ_SDA)
	{
		time++;
		if(time > 250)
		{
			IIC_Stop();
//			printf("no ack 22222\r\n");
			return 1;		//��Ӧ���źţ�ֹͣIIC������1
		}
		
	}
//	printf("ack 33333\r\n");
	SCL_L;
	return 0;				//��Ӧ���źţ�����0
}

/* ��������1Byte */
void IIC_Send_Byte(uint8_t txd)
{
	SDA_OUT();
	SCL_L;	//����ʱ�ӿ�ʼ���ݴ��䣬��ʵ����һ���Ѿ�Ϊ����
	for(int i = 0; i < 8; i++)
	{
		if((txd & 0x80))
			SDA_H;
		else
			SDA_L;
		SCL_H;
		IIC_Delay();
		SCL_L;
		IIC_Delay();
		txd <<= 1;
	}
}

/* �����Ӵӻ���ȡ1Byte 0����Ӧ��ӻ� 1��Ӧ��ӻ� */
uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t receive = 0;
	SDA_IN();
	for(int i = 0; i < 8; i++)
	{
		SCL_L;
		IIC_Delay();
		SCL_H;
		receive <<= 1;
		if(READ_SDA)
			receive |= 0x01;
		IIC_Delay();	
	}
	if(ack == 0)
		IIC_NAck();		//��Ӧ��
	else
		IIC_Ack();		//Ӧ��
	return receive;
}

/* IIC��ʱ */
void IIC_Delay(void)
{
//	Delay_us(4);
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
void Delay_us(unsigned long CountLing)
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

