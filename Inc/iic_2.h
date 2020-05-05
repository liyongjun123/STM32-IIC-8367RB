#ifndef __IIC_2_H
#define __IIC_2_H

#include "gpio.h"

//IO��������
#define SDA_2_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_2_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//#define SDA_2_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}
//#define SDA_2_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;}


#define SCL_2_H HAL_GPIO_WritePin(IIC_CLK_2_GPIO_Port, IIC_CLK_2_Pin, GPIO_PIN_SET)
#define SCL_2_L HAL_GPIO_WritePin(IIC_CLK_2_GPIO_Port, IIC_CLK_2_Pin, GPIO_PIN_RESET)

#define SDA_2_H HAL_GPIO_WritePin(IIC_SDA_2_GPIO_Port, IIC_SDA_2_Pin, GPIO_PIN_SET)
#define SDA_2_L HAL_GPIO_WritePin(IIC_SDA_2_GPIO_Port, IIC_SDA_2_Pin, GPIO_PIN_RESET)

//#define SCL_2_H GPIOB->BSRR = IIC_CLK_2_Pin;
//#define SCL_2_L GPIOB->BSRR = ~GPIO_PIN_All;

//#define SDA_2_H GPIOB->BSRR = IIC_SDA_2_GPIO_Port;
//#define SDA_2_L GPIOB->BSRR = ~GPIO_PIN_All;

#define READ_SDA_2 HAL_GPIO_ReadPin(IIC_SDA_2_GPIO_Port, IIC_SDA_2_Pin)

/* ����IIC��ʼ�ź� */
void IIC_Start_2(void);
/* ����IICֹͣ�ź� */
void IIC_Stop_2(void);
/* �������ظ�Ӧ���ź�0(ACK) */
void IIC_Ack_2(void);
/* �������ظ�Ӧ���ź�1(NACK) Ҳ�в�Ӧ��*/
void IIC_NAck_2(void);
/* �ȴ�Ӧ���ź� */
uint8_t IIC_Wait_Ack_2(void);
/* ��������1Byte */
void IIC_Send_Byte_2(uint8_t txd);
/* �����Ӵӻ���ȡ1Byte 0����Ӧ��ӻ� 1��Ӧ��ӻ� */
uint8_t IIC_Read_Byte_2(uint8_t ack);

/* ��ʱ����us */
void Delay_us_2(unsigned long CountLing);
/* IIC��ʱ */
void IIC_Delay_2(void);

#endif
