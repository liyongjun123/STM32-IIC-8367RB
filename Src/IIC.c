#include "IIC.h"

/* 产生IIC起始信号 */
void IIC_Start(void)
{
	SCL_L;
	SDA_OUT();	//SDA设为输出，养成好习惯，数据变化之前，一定拉低时钟线
	SDA_H;
	SCL_H;
	IIC_Delay();
	SDA_L;				//START:when CLK is high,DATA change form high to low 
	IIC_Delay();
	SCL_L;				//钳住I2C总线，准备发送或接收数据 
}

/* 产生IIC停止信号 */
void IIC_Stop(void)
{
	SCL_L;
	SDA_OUT();	//SDA设为输出
	SDA_L;
	SCL_H;
	IIC_Delay();
	SDA_H;			//STOP:when CLK is high DATA change form low to high
	IIC_Delay();
}

/* 主器件回复应答信号0(ACK) */
void IIC_Ack(void)
{
	SCL_L;
	SDA_OUT();
	SDA_L;				//数据线为低电平,20171211 2:53,搞到这么晚的原因终于找到了，数据线改变之前一定要把时钟线拉低，不然发送的不是起始信号就是停止信号
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L;				//再一个时钟下回复0
}

/* 主器件回复应答信号1(NACK) 也叫不应答*/
void IIC_NAck(void)
{
	SCL_L;
	SDA_OUT();
	SDA_H;				//数据线为高电平,20171211 2:53,搞到这么晚的原因终于找到了，数据线改变之前一定要把时钟线拉低，不然发送的不是起始信号就是停止信号
	IIC_Delay();
	SCL_H;
	IIC_Delay();
	SCL_L;				//再一个时钟下回复1
}

/* 等待应答信号 */
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
			return 1;		//无应答信号，停止IIC，返回1
		}
		
	}
//	printf("ack 33333\r\n");
	SCL_L;
	return 0;				//有应答信号，返回0
}

/* 主机发送1Byte */
void IIC_Send_Byte(uint8_t txd)
{
	SDA_OUT();
	SCL_L;	//拉低时钟开始数据传输，其实在上一步已经为低了
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

/* 主机从从机读取1Byte 0：不应答从机 1：应答从机 */
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
		IIC_NAck();		//不应答
	else
		IIC_Ack();		//应答
	return receive;
}

/* IIC延时 */
void IIC_Delay(void)
{
//	Delay_us(4);
	__NOP();	//12M时钟周期下每个NOP延时1us,72M时钟周期下延时1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
//	
		__NOP();	//12M时钟周期下每个NOP延时1us,72M时钟周期下延时1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
		__NOP();	//12M时钟周期下每个NOP延时1us,72M时钟周期下延时1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
		__NOP();	//12M时钟周期下每个NOP延时1us,72M时钟周期下延时1/6us
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
//	
//		__NOP();	//12M时钟周期下每个NOP延时1us,72M时钟周期下延时1/6us
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();
//	__NOP();

}

/* 延时函数us */
void Delay_us(unsigned long CountLing)
{
//    signed char i;
    while(CountLing--)
    {
//        i = 10;
//        while(i--);
//			__NOP();	//12M时钟周期下每个NOP延时1us,72M时钟周期下延时1/6us
//			__NOP();
//			__NOP();
//			__NOP();
//			__NOP();
//			__NOP();
    }
}

