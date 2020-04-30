#ifndef __IIC_H
#define __IIC_H

#include "gpio.h"

//IO方向设置
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

/* 产生IIC起始信号 */
void IIC_Start(void);
/* 产生IIC停止信号 */
void IIC_Stop(void);
/* 主器件回复应答信号0(ACK) */
void IIC_Ack(void);
/* 主器件回复应答信号1(NACK) 也叫不应答*/
void IIC_NAck(void);
/* 等待应答信号 */
uint8_t IIC_Wait_Ack(void);
/* 主机发送1Byte */
void IIC_Send_Byte(uint8_t txd);
/* 主机从从机读取1Byte 0：不应答从机 1：应答从机 */
uint8_t IIC_Read_Byte(uint8_t ack);

/* 延时函数us */
void Delay_us(unsigned long CountLing);
/* IIC延时 */
void IIC_Delay(void);

#endif
