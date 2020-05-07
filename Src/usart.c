/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include <stdlib.h>
#include "mdio.h"
#include "mpu6050.h"
#include "iic_2_phy.h"

#define BUFLEN 100
uint8_t receive_buf[BUFLEN];
uint16_t receive_len;
/* USER CODE END 0 */

UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_uart4_rx;

/* UART4 init function */
void MX_UART4_Init(void)
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();
  
    /**UART4 GPIO Configuration    
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Peripheral DMA init*/
  
    hdma_uart4_rx.Instance = DMA2_Channel3;
    hdma_uart4_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_uart4_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart4_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart4_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart4_rx.Init.Mode = DMA_NORMAL;
    hdma_uart4_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_uart4_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_uart4_rx);

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspInit 1 */

  /* USER CODE END UART4_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();
  
    /**UART4 GPIO Configuration    
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(UART4_IRQn);

  }
  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */

void gpio_op(uint8_t *buf);
void do_cmd(char *cmd);

/* 打开uart1接收中断 */

/* uart4接收处理函数 */
void uart4_process(uint8_t *buf, uint16_t len)
{

	if(len >= BUFLEN - 1)
	{
		printf("command is to long!\r\n");
		return;
	}
	
	buf[len] = '\0';
	
printf("%s\r\n", buf);
	
	if(strncmp("help", (char *)buf, 4) == 0)
	{
		help();
		
	}else if(strncmp("rpm", (char *)buf, 3) == 0)
	{
		/* read all 00 */
		/* read 00  00 */
		/* read 00  all */
		/* read all all */
		
		/* read */
		strtok((char *)buf, " ");
		
		/* phyad */
		char *pphyad = NULL;
		pphyad = strtok(NULL, " ");
		if(NULL == pphyad)
		{
			printf("rpm: para error!\r\n");
			printf("rpm  <phyAddr|all> <regAddr|all>\r\n");
			return;
		}
		
		/* regad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("rpm: para error!\r\n");
			printf("rpm  <phyAddr|all> <regAddr|all>\r\n");
			return;
		}
		
		if(strncmp("all", pphyad, 3) == 0)
		{
			if(strncmp("all", pregad, 3) == 0)
			{
				uint16_t value = 0;
				for(int i = 0; i < 32; i++)
				{
					for(int j = 0; j < 32; j++)
					{
						value = read_data(i, j);
						printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", i, j, value);
//						HAL_Delay(100);
					}
				}
			}else
			{
				
				uint32_t regad = 0;
				sscanf(pregad, "%x", &regad);
				
				uint16_t value = 0;
				for(int i = 0; i < 32; i++)
				{
					value = read_data(i, regad);
					printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", i, regad, value);
//					HAL_Delay(1000);
				}
			}
			
		}
		else
		{
			uint32_t phyad = 0;
	//		printf("p = %s\n", p);
			sscanf(pphyad, "%x", &phyad);
	//		printf("regad = %x\n", regad);
			
			if(strncmp("all", pregad, 3) == 0)
			{
				uint16_t value = 0;
				for(int i = 0; i < 32; i++)
				{
					value = read_data(phyad, i);
//					if(value != 0xffff)
						printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, i, value);
//					printf("666\r\n");
//					value = read_data(phyad, i);
//					if(value != 0xffff)
//						printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, i, value);
//					HAL_Delay(10);
				}
//				printf("777\r\n");
			}else
			{
				
				uint32_t regad = 0;
				sscanf(pregad, "%x", &regad);
				
				uint16_t value = 0;

				value = read_data(phyad, regad);
				printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);
			}
		}
		
	}else if(strncmp("wpm", (char *)buf, 3) == 0)
	{
		/*  */
		/* write */
		
		strtok((char *)buf, " ");
		
		/* phyad */
		char *pphyad = NULL;
		pphyad = strtok(NULL, " ");
		if(NULL == pphyad)
		{
			printf("write: para error!\r\n");
			printf("write <phyAddr> <regAddr> <data>\r\n");
			return;
		}
		
		/* regad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("write: para error!\r\n");
			printf("write <phyAddr> <regAddr> <data>\r\n");
			return;
		}
		
		/* value */
		char *pvalue = NULL;
		pvalue = strtok(NULL, " ");
		if(NULL == pvalue)
		{
			printf("write: para error!\r\n");
			printf("write <phyAddr> <regAddr> <data>\r\n");
			return;
		}
		
		uint32_t phyad = 0;
		sscanf(pphyad, "%x", &phyad);
		
		uint32_t regad = 0;
		sscanf(pregad, "%x", &regad);
		
		
		uint32_t value = 0;
		sscanf(pvalue, "%x", &value);
		
		write_data(phyad, regad, value);
		
		printf("write phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);
		
		uint32_t read_value = 0;
		read_value = read_data(phyad, regad);
//		if(value != 0xffff)
//		printf("read  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, read_value);
		
		write_data(phyad, regad, value);
		read_value = read_data(phyad, regad);
//		if(value != 0xffff)
//		printf("read  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, read_value);
		
		read_value = read_data(phyad, regad);
//		if(read_value != 0xffff)
		printf("read  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, read_value);
		
//		read_value = read_data(phyad, regad);
//		if(read_value != 0xffff)
//			printf("read  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, read_value);

	}
	else if(strncmp("r8i", (char *)buf, 3) == 0)
	{
				/* read */
		strtok((char *)buf, " ");
		
		/* phyad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("read: para error!\r\n");
			printf("read  <regAddr>\r\n");
			return;
		}
		
		uint32_t regad = 0;
		sscanf(pregad, "%x", &regad);
//		printf("regad = 0x%0X\r\n", regad);
		
		MPU6050_Read_Len(MPU6050_ADDR, regad, 2, buf);
	}
	else if(strncmp("w8i", (char *)buf, 3) == 0)
	{
		/* write */
		strtok((char *)buf, " ");
		
		/* regad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("write: para error!\r\n");
			printf("write <regAddr> <value>\r\n");
			return;
		}
		
		/* value */
		char *pvalue = NULL;
		pvalue = strtok(NULL, " ");
		if(NULL == pvalue)
		{
			printf("write: para error!\r\n");
			printf("write <regAddr> <value>\r\n");
			return;
		}
		
		uint32_t regad = 0;
		sscanf(pregad, "%x", &regad);
//		printf("regad = 0x%0X\r\n", regad);
		
		uint32_t value = 0;
		sscanf(pvalue, "%x", &value);
//		printf("value = 0x%0X\r\n", value);
		
		MPU6050_Write_Len(MPU6050_ADDR, regad, 2, value);
		MPU6050_Read_Len(MPU6050_ADDR, regad, 2, buf);
	}
	else if(strncmp("rpi", (char *)buf, 3) == 0)
	{
				/* read */
		strtok((char *)buf, " ");
		
		/* phyad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("read: para error!\r\n");
			printf("read  <regAddr>\r\n");
			return;
		}
		
		if(strncmp("all", (char *)pregad, 3) == 0)
		{
			for(int i = 0; i < 48; i++)
			{
				PHY_Read_Len(PHY_IIC_ADDR, i, 1, buf);
			}
		}else
		{
			uint32_t regad = 0;
			sscanf(pregad, "%x", &regad);
	//		printf("regad = 0x%0X\r\n", regad);
			
			PHY_Read_Len(PHY_IIC_ADDR, regad, 1, buf);
		}
		

	}
	else if(strncmp("wpi", (char *)buf, 3) == 0)
	{
		/* write */
		strtok((char *)buf, " ");
		
		/* regad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("write: para error!\r\n");
			printf("write <regAddr> <value>\r\n");
			return;
		}
		
		/* value */
		char *pvalue = NULL;
		pvalue = strtok(NULL, " ");
		if(NULL == pvalue)
		{
			printf("write: para error!\r\n");
			printf("write <regAddr> <value>\r\n");
			return;
		}
		uint32_t value = 0;
		sscanf(pvalue, "%x", &value);
		
		if(strncmp("all", (char *)pregad, 3) == 0)
		{
			for(int i = 0; i < 48; i++)
			{
				printf("write reg = 0x%02X value = 0x%02X\r\n", i, value);
				PHY_Write_Byte(i, value);
			}
		}
		else
		{
			uint32_t regad = 0;
			sscanf(pregad, "%x", &regad);
//		printf("regad = 0x%0X\r\n", regad);
		
		
//		printf("value = 0x%0X\r\n", value);
		printf("write reg = 0x%02X value = 0x%02X\r\n", regad, value);
		PHY_Write_Byte(regad, value);
//		PHY_Write_Byte(PHY_IIC_ADDR, regad, 2, value);
		PHY_Read_Len(PHY_IIC_ADDR, regad, 1, buf);
		}
		

	}
	else if(strncmp("P", (char *)buf, 1) == 0)
	{
		gpio_op(buf);
	}
	else if(strncmp("init8", (char *)buf, 5) == 0)
	{
		do_cmd("w8i 0x1305 0x10");
		do_cmd("w8i 0x13c3 0x01");
		do_cmd("w8i 0x1307 0x08");
		do_cmd("w8i 0x13c5 0x08");
		do_cmd("w8i 0x1310 0x1076");
		do_cmd("w8i 0x1311 0x1076");

	}
	else if(strncmp("initp", (char *)buf, 5) == 0)
	{
		do_cmd("PD12 SET");
		do_cmd("wpi 0x00 0x0");
		do_cmd("wpi 0x01 0x0");
		do_cmd("wpi 0x02 0x0");
		do_cmd("wpi 0x03 0x0");
		do_cmd("wpi 0x04 0x0");
		do_cmd("wpi 0x05 0x0");
		do_cmd("wpi 0x06 0x0");
		do_cmd("wpi 0x07 0x0");
		do_cmd("wpi 0x08 0x0");
		do_cmd("wpi 0x09 0x0");
		do_cmd("wpi 0x0a 0x0");
		do_cmd("wpi 0x0b 0x0");
		do_cmd("wpi 0x0c 0x0");
		do_cmd("wpi 0x0d 0x0");
		do_cmd("wpi 0x0e 0x0");
		do_cmd("wpi 0x0f 0x0");
		do_cmd("wpi 0x10 0x0");
		do_cmd("wpi 0x11 0x0");
		do_cmd("wpi 0x12 0x0");
		do_cmd("wpi 0x13 0x0");
		do_cmd("wpi 0x14 0x0");
		do_cmd("wpi 0x15 0x0");
		do_cmd("wpi 0x16 0x0");
		do_cmd("wpi 0x17 0x0");
		do_cmd("wpi 0x18 0x0");
		do_cmd("wpi 0x19 0x0");
		do_cmd("wpi 0x1a 0x0");
		do_cmd("wpi 0x1b 0x0");
		do_cmd("wpi 0x1c 0x0");
		do_cmd("wpi 0x1d 0x0");
		do_cmd("wpi 0x1e 0x0");
		do_cmd("wpi 0x1f 0x0");
		do_cmd("wpi 0x20 0x0");
		do_cmd("wpi 0x21 0x0");
		do_cmd("wpi 0x22 0x0");
		do_cmd("wpi 0x23 0x0");
		do_cmd("wpi 0x24 0x0");
		do_cmd("wpi 0x25 0x0");
		do_cmd("wpi 0x26 0x0");
		do_cmd("wpi 0x27 0x0");
		do_cmd("wpi 0x28 0x0");
		do_cmd("wpi 0x29 0x0");
		do_cmd("wpi 0x2a 0x0");
		do_cmd("wpi 0x2b 0x0");
		do_cmd("wpi 0x2c 0x0");
		do_cmd("wpi 0x2d 0x0");
		do_cmd("wpi 0x2e 0x0");
		do_cmd("wpi 0x2f 0x41");

// 1		
		do_cmd("PD8 RESET");
		do_cmd("wpi 0x05 0x11");
		
		do_cmd("wpm 11 0x1f 0x0");
		do_cmd("wpm 11 0x09 0x0300");
		do_cmd("wpm 11 0x00 0x1140");
		do_cmd("wpm 11 0x17 0x7C02");
		do_cmd("wpm 11 0x18 0xffaa");
		do_cmd("wpm 11 0x19 0xf6db");
		do_cmd("wpm 11 0x1b 0x400");
		do_cmd("wpm 11 0x1f 0x1");
		do_cmd("wpm 11 0x10 0xa400");
		do_cmd("wpm 11 0x11 0x2108");
		do_cmd("wpm 11 0x12 0xe0d0");
		do_cmd("wpm 11 0x14 0x1790");
		do_cmd("wpm 11 0x18 0xcb");
		do_cmd("wpm 11 0x1e 0x8680");
		do_cmd("wpm 11 0x1f 0x02");
		do_cmd("wpm 11 0x10 0x7fb6");
		do_cmd("wpm 11 0x11 0x3773");
		do_cmd("wpm 11 0x13 0x6db");
		
		do_cmd("PD8 SET");
#if 1
// 2		
		do_cmd("PD9 RESET");
		do_cmd("wpi 0x06 0x12");
		
		do_cmd("wpm 12 0x1f 0x0");
		do_cmd("wpm 12 0x09 0x0300");
		do_cmd("wpm 12 0x00 0x1140");
		do_cmd("wpm 12 0x17 0x7C02");
		do_cmd("wpm 12 0x18 0xffaa");
		do_cmd("wpm 12 0x19 0xf6db");
		do_cmd("wpm 12 0x1b 0x400");
		do_cmd("wpm 12 0x1f 0x1");
		do_cmd("wpm 12 0x10 0xa400");
		do_cmd("wpm 12 0x11 0x2108");
		do_cmd("wpm 12 0x12 0xe0d0");
		do_cmd("wpm 12 0x14 0x1790");
		do_cmd("wpm 12 0x18 0xcb");
		do_cmd("wpm 12 0x1e 0x8680");
		do_cmd("wpm 12 0x1f 0x02");
		do_cmd("wpm 12 0x10 0x7fb6");
		do_cmd("wpm 12 0x11 0x3773");
		do_cmd("wpm 12 0x13 0x6db");
		
		do_cmd("PD9 SET");		

// 3		
		do_cmd("PD10 RESET");
		do_cmd("wpi 0x07 0x13");
		
		do_cmd("wpm 13 0x1f 0x0");
		do_cmd("wpm 13 0x09 0x0300");
		do_cmd("wpm 13 0x00 0x1140");
		do_cmd("wpm 13 0x17 0x7C02");
		do_cmd("wpm 13 0x18 0xffaa");
		do_cmd("wpm 13 0x19 0xf6db");
		do_cmd("wpm 13 0x1b 0x400");
		do_cmd("wpm 13 0x1f 0x1");
		do_cmd("wpm 13 0x10 0xa400");
		do_cmd("wpm 13 0x11 0x2108");
		do_cmd("wpm 13 0x12 0xe0d0");
		do_cmd("wpm 13 0x14 0x1790");
		do_cmd("wpm 13 0x18 0xcb");
		do_cmd("wpm 13 0x1e 0x8680");
		do_cmd("wpm 13 0x1f 0x02");
		do_cmd("wpm 13 0x10 0x7fb6");
		do_cmd("wpm 13 0x11 0x3773");
		do_cmd("wpm 13 0x13 0x6db");
		
		do_cmd("PD10 SET");	
		
// 3		
		do_cmd("PD11 RESET");
		do_cmd("wpi 0x08 0x14");
		
		do_cmd("wpm 14 0x1f 0x0");
		do_cmd("wpm 14 0x09 0x0300");
		do_cmd("wpm 14 0x00 0x1140");
		do_cmd("wpm 14 0x17 0x7C02");
		do_cmd("wpm 14 0x18 0xffaa");
		do_cmd("wpm 14 0x19 0xf6db");
		do_cmd("wpm 14 0x1b 0x400");
		do_cmd("wpm 14 0x1f 0x1");
		do_cmd("wpm 14 0x10 0xa400");
		do_cmd("wpm 14 0x11 0x2108");
		do_cmd("wpm 14 0x12 0xe0d0");
		do_cmd("wpm 14 0x14 0x1790");
		do_cmd("wpm 14 0x18 0xcb");
		do_cmd("wpm 14 0x1e 0x8680");
		do_cmd("wpm 14 0x1f 0x02");
		do_cmd("wpm 14 0x10 0x7fb6");
		do_cmd("wpm 14 0x11 0x3773");
		do_cmd("wpm 14 0x13 0x6db");
		
		do_cmd("PD11 SET");	
#endif
	}
	else if(strncmp("init2", (char *)buf, 5) == 0)
	{
		do_cmd("PD12 SET");
		do_cmd("wpi 0x00 0x0");
		do_cmd("wpi 0x01 0x0");
		do_cmd("wpi 0x02 0x0");
		do_cmd("wpi 0x03 0x0");
		do_cmd("wpi 0x04 0x0");
		do_cmd("wpi 0x05 0x0");
		do_cmd("wpi 0x06 0x0");
		do_cmd("wpi 0x07 0x0");
		do_cmd("wpi 0x08 0x0");
		do_cmd("wpi 0x09 0x0");
		do_cmd("wpi 0x0a 0x0");
		do_cmd("wpi 0x0b 0x0");
		do_cmd("wpi 0x0c 0x0");
		do_cmd("wpi 0x0d 0x0");
		do_cmd("wpi 0x0e 0x0");
		do_cmd("wpi 0x0f 0x0");
		do_cmd("wpi 0x10 0x0");
		do_cmd("wpi 0x11 0x0");
		do_cmd("wpi 0x12 0x0");
		do_cmd("wpi 0x13 0x0");
		do_cmd("wpi 0x14 0x0");
		do_cmd("wpi 0x15 0x0");
		do_cmd("wpi 0x16 0x0");
		do_cmd("wpi 0x17 0x0");
		do_cmd("wpi 0x18 0x0");
		do_cmd("wpi 0x19 0x0");
		do_cmd("wpi 0x1a 0x0");
		do_cmd("wpi 0x1b 0x0");
		do_cmd("wpi 0x1c 0x0");
		do_cmd("wpi 0x1d 0x0");
		do_cmd("wpi 0x1e 0x0");
		do_cmd("wpi 0x1f 0x0");
		do_cmd("wpi 0x20 0x0");
		do_cmd("wpi 0x21 0x0");
		do_cmd("wpi 0x22 0x0");
		do_cmd("wpi 0x23 0x0");
		do_cmd("wpi 0x24 0x0");
		do_cmd("wpi 0x25 0x0");
		do_cmd("wpi 0x26 0x0");
		do_cmd("wpi 0x27 0x0");
		do_cmd("wpi 0x28 0x0");
		do_cmd("wpi 0x29 0x0");
		do_cmd("wpi 0x2a 0x0");
		do_cmd("wpi 0x2b 0x0");
		do_cmd("wpi 0x2c 0x0");
		do_cmd("wpi 0x2d 0x0");
		do_cmd("wpi 0x2e 0x0");
		do_cmd("wpi 0x2f 0x41");

// 1		
		do_cmd("PD8 RESET");
		do_cmd("wpi 0x05 0x1");
		
		do_cmd("wpm 1 0x1f 0x0");
		do_cmd("wpm 1 0x09 0x0300");
		do_cmd("wpm 1 0x00 0x1140");
		do_cmd("wpm 1 0x17 0x7f82");
		do_cmd("wpm 1 0x18 0xffff");
		do_cmd("wpm 1 0x19 0xffff");
		do_cmd("wpm 1 0x1b 0x800");
		do_cmd("wpm 1 0x1f 0x1");
		do_cmd("wpm 1 0x10 0xa40c");
		do_cmd("wpm 1 0x11 0x2108");
		do_cmd("wpm 1 0x12 0xe0d0");
		do_cmd("wpm 1 0x14 0x1790");
		do_cmd("wpm 1 0x18 0xcb");
		do_cmd("wpm 1 0x1e 0x8680");
		do_cmd("wpm 1 0x1f 0x02");
		do_cmd("wpm 1 0x10 0x7fb6");
		do_cmd("wpm 1 0x11 0x7777");
		do_cmd("wpm 1 0x13 0x6db");
		
		do_cmd("PD8 SET");
#if 1
// 2		
		do_cmd("PD9 RESET");
		do_cmd("wpi 0x06 0x2");
		
		do_cmd("wpm 2 0x1f 0x0");
		do_cmd("wpm 2 0x09 0x0300");
		do_cmd("wpm 2 0x00 0x1140");
		do_cmd("wpm 2 0x17 0x7f82");
		do_cmd("wpm 2 0x18 0xffff");
		do_cmd("wpm 2 0x19 0xffff");
		do_cmd("wpm 2 0x1b 0x800");
		do_cmd("wpm 2 0x1f 0x1");
		do_cmd("wpm 2 0x10 0xa40c");
		do_cmd("wpm 2 0x11 0x2108");
		do_cmd("wpm 2 0x12 0xe0d0");
		do_cmd("wpm 2 0x14 0x1790");
		do_cmd("wpm 2 0x18 0xcb");
		do_cmd("wpm 2 0x1e 0x8680");
		do_cmd("wpm 2 0x1f 0x02");
		do_cmd("wpm 2 0x10 0x7fb6");
		do_cmd("wpm 2 0x11 0x7777");
		do_cmd("wpm 2 0x13 0x6db");
		
		do_cmd("PD9 SET");		

// 3		
		do_cmd("PD10 RESET");
		do_cmd("wpi 0x07 0x3");
		
		do_cmd("wpm 3 0x1f 0x0");
		do_cmd("wpm 3 0x09 0x0300");
		do_cmd("wpm 3 0x00 0x1140");
		do_cmd("wpm 3 0x17 0x7f82");
		do_cmd("wpm 3 0x18 0xffff");
		do_cmd("wpm 3 0x19 0xffff");
		do_cmd("wpm 3 0x1b 0x800");
		do_cmd("wpm 3 0x1f 0x1");
		do_cmd("wpm 3 0x10 0xa40c");
		do_cmd("wpm 3 0x11 0x2108");
		do_cmd("wpm 3 0x12 0xe0d0");
		do_cmd("wpm 3 0x14 0x1790");
		do_cmd("wpm 3 0x18 0xcb");
		do_cmd("wpm 3 0x1e 0x8680");
		do_cmd("wpm 3 0x1f 0x02");
		do_cmd("wpm 3 0x10 0x7fb6");
		do_cmd("wpm 3 0x11 0x7777");
		do_cmd("wpm 3 0x13 0x6db");
		
		do_cmd("PD10 SET");	
		
// 3		
		do_cmd("PD11 RESET");
		do_cmd("wpi 0x08 0x4");
		
		do_cmd("wpm 4 0x1f 0x0");
		do_cmd("wpm 4 0x09 0x0300");
		do_cmd("wpm 4 0x00 0x1140");
		do_cmd("wpm 4 0x17 0x7f82");
		do_cmd("wpm 4 0x18 0xffff");
		do_cmd("wpm 4 0x19 0xffff");
		do_cmd("wpm 4 0x1b 0x800");
		do_cmd("wpm 4 0x1f 0x1");
		do_cmd("wpm 4 0x10 0xa40c");
		do_cmd("wpm 4 0x11 0x2108");
		do_cmd("wpm 4 0x12 0xe0d0");
		do_cmd("wpm 4 0x14 0x1790");
		do_cmd("wpm 4 0x18 0xcb");
		do_cmd("wpm 4 0x1e 0x8680");
		do_cmd("wpm 4 0x1f 0x02");
		do_cmd("wpm 4 0x10 0x7fb6");
		do_cmd("wpm 4 0x11 0x7777");
		do_cmd("wpm 4 0x13 0x6db");
		
		do_cmd("PD11 SET");	
		
		do_cmd("PD8 RESET");	
		do_cmd("wpm 1 0x1f 0x0");
		do_cmd("wpm 1 0x09 0x2300");
		do_cmd("PD8 SET");	
		
		do_cmd("PD9 RESET");	
		do_cmd("wpm 2 0x1f 0x0");
		do_cmd("wpm 2 0x09 0x2300");
		do_cmd("PD9 SET");	
		
		do_cmd("PD10 RESET");	
		do_cmd("wpm 3 0x1f 0x0");
		do_cmd("wpm 3 0x09 0x2300");
		do_cmd("PD10 SET");	
		
		do_cmd("PD11 RESET");	
		do_cmd("wpm 4 0x1f 0x0");
		do_cmd("wpm 4 0x09 0x2300");
		do_cmd("PD11 SET");	
#endif
	}
	else
	{
		printf("unknown cmd!\r\n");
	}
	
	
	
	
	printf("\r\n");
	
}


void do_cmd(char *cmd)
{
	char buf[100] = {0};
		
	strncpy(buf, cmd, sizeof(buf) - 1);
	uart4_process((uint8_t *)buf, strlen(buf) + 1);
}

void gpio_op(uint8_t *buf)
{
//	if(strncmp("PA1", (char *)buf, 3) == 0)
//	{
//		/* regad */
//		char *p = NULL;
//		p = strtok(NULL, " ");
//		if(NULL == p)
//		{
//			printf("PA1 SET\r\n");
//			printf("PA1 RESET\r\n");
//			return;
//		}
//		
//		if(strncmp("SET", p, 3) == 0)
//		{
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
//		}
//		else
//		{
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
//		}
//	}
//	else if(strncmp("PE10", (char *)buf, 4) == 0)
//	{
	strtok((char *)buf, " ");

		char *p = NULL;
		p = strtok(NULL, " ");
		if(NULL == p)
		{
			printf("PA1 SET\r\n");
			printf("PA1 RESET\r\n");
			return;
		}
		
		int value = 0;
		if(strncmp("SET", p, 3) == 0)
		{
			value = 1;
		}
		
		int position;
		position = atoi((char *)(buf + 2));
		switch((char)buf[1])
		{
			case 'A':
				HAL_GPIO_WritePin(GPIOA, 1 << position, (GPIO_PinState)value);
			break;
			case 'B':
				HAL_GPIO_WritePin(GPIOB, 1 << position, (GPIO_PinState)value);
			break;
			
			case 'D':
				HAL_GPIO_WritePin(GPIOD, 1 << position, (GPIO_PinState)value);
			break;
			
			case 'E':
				HAL_GPIO_WritePin(GPIOE, 1 << position, (GPIO_PinState)value);
			break;
				
		}
		
		
//	}
}

void uart4_start_receive_it(void)
{
	__HAL_UART_CLEAR_IDLEFLAG(&huart4);
	huart4.State = HAL_UART_STATE_READY;
	__HAL_DMA_DISABLE(huart4.hdmarx);
	__HAL_DMA_CLEAR_FLAG(huart4.hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(huart4.hdmarx));
	__HAL_UNLOCK(huart4.hdmarx);
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart4, receive_buf, BUFLEN);
}

/* uart1接收函数 */
void uart4_receive(void)
{
	/* 接收到的数据长度 */
	receive_len = BUFLEN - huart4.hdmarx->Instance->CNDTR;

	/* uart1接收处理函数 */
	uart4_process(receive_buf, receive_len);
	
//	debug_data("485_rx", rs485.rs485_message.buf, rs485.rs485_message.len);
	
	/* 开始串口空闲中断DMA接收 */
	uart4_start_receive_it();
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
