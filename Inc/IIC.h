#ifndef __IIC_H
#define __IIC_H

#include "gpio.h"

//IO��������
//#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;}

#define SCL_H HAL_GPIO_WritePin(IIC_CLK_GPIO_Port, IIC_CLK_Pin, GPIO_PIN_SET)
#define SCL_L HAL_GPIO_WritePin(IIC_CLK_GPIO_Port, IIC_CLK_Pin, GPIO_PIN_RESET)

#define SDA_H HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_PIN_SET)
#define SDA_L HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_PIN_RESET)

//#define SCL_H GPIOB->BSRR = IIC_CLK_Pin;
//#define SCL_L GPIOB->BSRR = ~GPIO_PIN_All;

//#define SDA_H GPIOB->BSRR = IIC_SDA_GPIO_Port;
//#define SDA_L GPIOB->BSRR = ~GPIO_PIN_All;

#define READ_SDA HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port, IIC_SDA_Pin)

/* ����IIC��ʼ�ź� */
void IIC_Start(void);
/* ����IICֹͣ�ź� */
void IIC_Stop(void);
/* �������ظ�Ӧ���ź�0(ACK) */
void IIC_Ack(void);
/* �������ظ�Ӧ���ź�1(NACK) Ҳ�в�Ӧ��*/
void IIC_NAck(void);
/* �ȴ�Ӧ���ź� */
uint8_t IIC_Wait_Ack(void);
/* ��������1Byte */
void IIC_Send_Byte(uint8_t txd);
/* �����Ӵӻ���ȡ1Byte 0����Ӧ��ӻ� 1��Ӧ��ӻ� */
uint8_t IIC_Read_Byte(uint8_t ack);

/* ��ʱ����us */
void Delay_us(unsigned long CountLing);
/* IIC��ʱ */
void IIC_Delay(void);

#endif
