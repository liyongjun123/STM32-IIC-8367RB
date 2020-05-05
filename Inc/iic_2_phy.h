#ifndef __IIC_2_PHY_H
#define __IIC_2_PHY_H

#include "iic_2.h"

//如果AD0脚(9脚)接地,IIC地址为0X68(不包含最低位).
//如果接V3.3,则IIC地址为0X69(不包含最低位).
//#define PHY_IIC_ADDR				0X68
//#define PHY_IIC_ADDR				0X5C
#define PHY_IIC_ADDR				0X22





/* IIC写1Byte */
uint8_t Pyh_Write_Byte(uint8_t reg, uint8_t data);




/* IIC写1Byte */
uint8_t PHY_Write_Byte(uint8_t reg, uint8_t data);
/* IIC连续读取 */
uint8_t PHY_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
#endif
