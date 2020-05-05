#ifndef __IIC_2_PHY_H
#define __IIC_2_PHY_H

#include "iic_2.h"

//���AD0��(9��)�ӵ�,IIC��ַΪ0X68(���������λ).
//�����V3.3,��IIC��ַΪ0X69(���������λ).
//#define PHY_IIC_ADDR				0X68
//#define PHY_IIC_ADDR				0X5C
#define PHY_IIC_ADDR				0X22





/* IICд1Byte */
uint8_t Pyh_Write_Byte(uint8_t reg, uint8_t data);




/* IICд1Byte */
uint8_t PHY_Write_Byte(uint8_t reg, uint8_t data);
/* IIC������ȡ */
uint8_t PHY_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
#endif
