#ifndef __MPU6050_H
#define __MPU6050_H

#include "IIC.h"

//���AD0��(9��)�ӵ�,IIC��ַΪ0X68(���������λ).
//�����V3.3,��IIC��ַΪ0X69(���������λ).
//#define MPU6050_ADDR				0X68
#define MPU6050_ADDR				0X5C

#define MPU_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define MPU_CFG_REG				0X1A	//���üĴ���
#define MPU_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���

#define MPU_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define MPU_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���

#define MPU_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define MPU_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1


#define MPU_TEMP_OUTH_REG		0X41	//�¶�ֵ��8λ�Ĵ���
#define MPU_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���

/* ��ʼ��MPU6050 */
uint8_t MPU6050_Init(void);
/* ��ȡ�¶� */
uint16_t MPU6050_Read_Temperature(void);
/* IIC������ȡ */
uint8_t MPU6050_Read_Len(uint8_t addr, uint16_t reg, uint8_t len, uint8_t *buf);
/* IICд1Byte */
uint8_t MPU6050_Write_Byte(uint8_t reg, uint8_t data);

/* IICд */
uint8_t MPU6050_Write_Len(uint8_t addr, uint16_t reg, uint8_t len, uint16_t value);
#endif
