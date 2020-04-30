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
#include "mdio.h"
#include "mpu6050.h"

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
//	printf("len = %d\n", len);
//	printf("buf = %s\n", buf);
	
	
	if(strncmp("help", (char *)buf, 4) == 0)
	{
		help();
		
	}else if(strncmp("read", (char *)buf, 4) == 0)
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
			printf("read: para error!\r\n");
			printf("read  <phyAddr|all> <regAddr|all>\r\n");
			return;
		}
		
		/* regad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("read: para error!\r\n");
			printf("read  <phyAddr|all> <regAddr|all>\r\n");
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
					printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, i, value);
//					printf("666\r\n");
//					value = read_data(phyad, i);
//					printf("read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, i, value);
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
		
	}else if(strncmp("write", (char *)buf, 5) == 0)
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
		
		value = read_data(phyad, regad);
		printf("eead  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);

		value = read_data(phyad, regad);
		printf("eead  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);

	}
	else if(strncmp("8367read", (char *)buf, 8) == 0)
	{
		/* 8367read all 00 */
		/* 8367read 00  00 */
		/* 8367read 00  all */
		/* 8367read all all */
		
		/* read */
		strtok((char *)buf, " ");
		
		/* phyad */
		char *pphyad = NULL;
		pphyad = strtok(NULL, " ");
		if(NULL == pphyad)
		{
			printf("8367read: para error!\r\n");
			printf("8367read  <phyAddr|all> <regAddr|all>\r\n");
			return;
		}
		
		/* regad */
		char *pregad = NULL;
		pregad = strtok(NULL, " ");
		if(NULL == pregad)
		{
			printf("8367read: para error!\r\n");
			printf("8367read  <phyAddr|all> <regAddr|all>\r\n");
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
						value = read_data_8367(i, j);
						printf("8367read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", i, j, value);
//						HAL_Delay(10);
					}
				}
			}else
			{
				
				uint32_t regad = 0;
				sscanf(pregad, "%x", &regad);
				
				uint16_t value = 0;
				for(int i = 0; i < 32; i++)
				{
					value = read_data_8367(i, regad);
					printf("8367read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", i, regad, value);
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
					value = read_data_8367(phyad, i);
					printf("8367read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, i, value);
//					HAL_Delay(1);
				}
			}else
			{
				
				uint32_t regad = 0;
				sscanf(pregad, "%x", &regad);
				
				uint16_t value = 0;

				value = read_data_8367(phyad, regad);
				printf("8367read phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);
			}
		}
		
	}else if(strncmp("8367write", (char *)buf, 9) == 0)
	{
		/* write 00 1f 3 */
		
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
		
		write_data_8367(phyad, regad, value);
		printf("8367write phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);
		
		value = read_data_8367(phyad, regad);
		printf("8367read  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);
		
		value = read_data_8367(phyad, regad);
		printf("8367read  phy = 0x%02X reg = 0x%02X value = 0x%04X\r\n", phyad, regad, value);

	}else if(strncmp("riic", (char *)buf, 4) == 0)
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
	else if(strncmp("wiic", (char *)buf, 4) == 0)
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
	else
	{
		printf("unknown cmd!\r\n");
	}
	
	
	
	
	printf("\r\n");
	
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
