#ifndef __MPU6050_H
#define __MPU6050_H

#include "IIC.h"

//如果AD0脚(9脚)接地,IIC地址为0X68(不包含最低位).
//如果接V3.3,则IIC地址为0X69(不包含最低位).
//#define MPU6050_ADDR				0X68
#define MPU6050_ADDR				0X5C

#define MPU_SAMPLE_RATE_REG		0X19	//采样频率分频器
#define MPU_CFG_REG				0X1A	//配置寄存器
#define MPU_FIFO_EN_REG			0X23	//FIFO使能寄存器

#define MPU_INTBP_CFG_REG		0X37	//中断/旁路设置寄存器
#define MPU_INT_EN_REG			0X38	//中断使能寄存器

#define MPU_USER_CTRL_REG		0X6A	//用户控制寄存器
#define MPU_PWR_MGMT1_REG		0X6B	//电源管理寄存器1


#define MPU_TEMP_OUTH_REG		0X41	//温度值高8位寄存器
#define MPU_TEMP_OUTL_REG		0X42	//温度值低8位寄存器

/* 初始化MPU6050 */
uint8_t MPU6050_Init(void);
/* 读取温度 */
uint16_t MPU6050_Read_Temperature(void);
/* IIC连续读取 */
uint8_t MPU6050_Read_Len(uint8_t addr, uint16_t reg, uint8_t len, uint8_t *buf);
/* IIC写1Byte */
uint8_t MPU6050_Write_Byte(uint8_t reg, uint8_t data);

/* IIC写 */
uint8_t MPU6050_Write_Len(uint8_t addr, uint16_t reg, uint8_t len, uint16_t value);
#endif
