#include "mdio.h"
#include "stm32f1xx_hal.h"


void Delay_us2(unsigned long CountLing)
{
    signed char i;
    while(CountLing--)
    {
        i = 10;
        while(i--);
    }
}
void delay(void)
{
	Delay_us2(10);
}

/* 设置MDIO引脚为输出模式 */
static void mdio_output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = MDIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MDIO_GPIO_Port, &GPIO_InitStruct);
}

/* 设置MDIO引脚为输入模式 */
static void mdio_input(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.Pin = MDIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MDIO_GPIO_Port, &GPIO_InitStruct);
}

/* MDIO 单纯clk 无用 */
void mdio_clk(void)
{
	uint8_t i;
	
	HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
	/* 将io切换为输出模式 */
  mdio_output();	
	
	
	
	for(i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
	}
}

/* 向MDIO写一个字节 */
void mdio_write_byte(uint8_t dat)
{
	uint8_t i;
	
	/* 将io切换为输出模式 */
  mdio_output();	
	
	for(i = 0; i < 8; i++)
	{
		if(dat & 0x01)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat >>= 1;
	}
}

/* MDIO read start */
void mdio_read_start(void)
{
	uint8_t dat = 0x06;
	uint8_t i;
	
	/* 将io切换为输出模式 */
  mdio_output();	
	
	for(i = 0; i < 4; i++)
	{
		if(dat & 0x01)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat >>= 1;
	}
}

/* PHY address */
void phyad(void)
{
	uint8_t dat = 0x00;
	uint8_t i;
	
	/* 将io切换为输出模式 */
  mdio_output();	
	
	for(i = 0; i < 5; i++)
	{
		if(dat & 0x01)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat >>= 1;
	}
}

/* REG address */
void regad(void)
{
	uint8_t dat = 0x00;
	uint8_t i;
	
	/* 将io切换为输出模式 */
  mdio_output();	
	
	for(i = 0; i < 5; i++)
	{
		if(dat & 0x01)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat >>= 1;
	}
}


/* MDIO turn around */
void turn_around(void)
{
	uint8_t dat = 0x01;
	uint8_t i;
	
	/* 将io切换为输出模式 */
  mdio_output();	
	
	for(i = 0; i < 2; i++)
	{
		if(dat & 0x01)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat >>= 1;
	}
}

/* 从MDIO读取一个字节 */
uint8_t mdio_read_byte(void)
{
	uint8_t i;
	uint8_t dat = 0;
	
	/* 将io切换为输入模数 */
	mdio_input();
	
	for(i = 0; i < 8; i++)
	{
		dat >>= 1;
		
		if(GPIO_PIN_SET == HAL_GPIO_ReadPin(MDIO_GPIO_Port, MDIO_Pin))
			dat |= 0x80;

		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);	
	}
	
	return dat;
}

uint16_t all(uint8_t regad);

uint16_t read_data2(uint8_t phyad, uint8_t regad)
{
//	mdio_clk();
//	mdio_read_start();
////	mdio_write_byte(0x55);
//	phyad();
//	regad();
//	turn_around();
//	mdio_read_byte();
//	mdio_read_byte();
	
//	 return all(regad);
	
/* 0. 空闲 IDLE mdio_clk */
	uint8_t i;
	
	HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
	/* 将io切换为输出模式 */
  mdio_output();	
	
	
	for(i = 0; i < 32; i++)
	{
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
	}
	
/* 1. 起始位01 + 2. 读命令10 mdio_read_start */
	uint8_t dat = 0x06;
	
	/* 将io切换为输出模式 */
	//  mdio_output();	
	
	for(i = 0; i < 4; i++)
	{
		if(dat & 0x08)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}
	
	
/* 3. PHY地址 phyad */
		/* 将io切换为输出模式 */
//  mdio_output();	
	dat = phyad;
	for(i = 0; i < 5; i++)
	{
		if(dat & 0x10)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}
	
/* 4. 寄存器地址 regad */
	dat = regad;
//	for(i = 0; i < 5; i++)
//	{
//		if(dat & 0x01)
//			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
//		else
//			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
//		dat >>= 1;
//	}
	
	for(i = 0; i < 5; i++)
	{
		if(dat & 0x10)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		if(i < 4)
			HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}

/* 5. 转场10 turn around */
	dat = 0x00;
	
	/* 将io切换为输出模式 */
//  mdio_output();	
HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
//	mdio_input();
#if 0
	for(i = 0; i < 2; i++)
	{
//		if(dat & 0x02)
//			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
//		else
//			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
//HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}
#endif
#if 1
	HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
	
	mdio_input();
	
	HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);


uint16_t out_data = 0x0000;	
//	if(GPIO_PIN_RESET != HAL_GPIO_ReadPin(MDIO_GPIO_Port, MDIO_Pin))
//	{
////		printf("gaoooooo\r\n");
//	
#endif
//	
//	/* 7. 读取16bits数据 */	
//			/* 将io切换为输入模数 */
//	//	mdio_input();
////		uint16_t out_data = 0x0000;
//		

//		for(i = 0; i < 16; i++)
//		{
//			out_data <<= 1;
//			
//			if(GPIO_PIN_SET == HAL_GPIO_ReadPin(MDIO_GPIO_Port, MDIO_Pin))
//				out_data |= 0x0001;

//			HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);	
//		}
//		
//		for(i = 0; i < 8; i++)
//		{
//			HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
//		}
//	
//		return 0xFFFF;
//	}
	mdio_input();
	for(i = 0; i < 16; i++)
	{
		out_data <<= 1;
		
		if(GPIO_PIN_SET == HAL_GPIO_ReadPin(MDIO_GPIO_Port, MDIO_Pin))
			out_data |= 0x0001;

		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);	
	}
	
//	for(i = 0; i < 8; i++)
//	{
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
//	}
	
	return out_data;
	
}


void write_data2(uint8_t phyad, uint8_t regad, uint16_t out_data)
{

/* 0. 空闲 IDLE mdio_clk */
	uint8_t i;
	
	HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
	/* 将io切换为输出模式 */
  mdio_output();	
	
	for(i = 0; i < 32; i++)
	{
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
	}
	
	
/* 1. 起始位01 + 2. 写命令01 mdio_read_start */
	uint8_t dat = 0x05;
	
	/* 将io切换为输出模式 */
	//  mdio_output();	
	
	for(i = 0; i < 4; i++)
	{
		if(dat & 0x08)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}
	
	
/* 3. PHY地址 phyad */
		/* 将io切换为输出模式 */
//  mdio_output();	
	dat = phyad;
	for(i = 0; i < 5; i++)
	{
		if(dat & 0x10)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}
	
/* 4. 寄存器地址 regad */
	dat = regad;
//	for(i = 0; i < 5; i++)
//	{
//		if(dat & 0x01)
//			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
//		else
//			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
//		dat >>= 1;
//	}
	
	for(i = 0; i < 5; i++)
	{
		if(dat & 0x10)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}

/* 5. 转场10 turn around */
	dat = 0x02;
	
	/* 将io切换为输出模式 */
//  mdio_output();	
	
	for(i = 0; i < 2; i++)
	{
		if(dat & 0x02)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		dat <<= 1;
	}
	
/* 7. 写16bits数据 */	
	
//	for(i = 0; i < 16; i++)
//	{
//		out_data >>= 1;
//		
//		if(GPIO_PIN_SET == HAL_GPIO_ReadPin(MDIO_GPIO_Port, MDIO_Pin))
//			out_data |= 0x8000;

//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);	
//	}
	
	for(i = 0; i < 16; i++)
	{
		if(out_data & 0x8000)
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET);
		out_data <<= 1;
	}
	
	return;
}


#define MDC_MDIO_CTRL0_REG 			31
#define MDC_MDIO_ADDRESS_REG 		23
#define MDC_MDIO_CTRL1_REG			21
#define MDC_MDIO_DATA_READ_REG	25

#define MDC_MDIO_ADDR_OP	0x000E
#define MDC_MDIO_READ_OP	0x0001

uint16_t read_data_8367(uint8_t phyad, uint16_t regad)
{
	/* step 1. write address control code to register 31 */
	write_data(phyad, MDC_MDIO_CTRL0_REG, MDC_MDIO_ADDR_OP);
	/* step 2. write address to register 23 */
	write_data(phyad, MDC_MDIO_ADDRESS_REG, regad);
	/* step 3. write read control code to register 21 */
	write_data(phyad, MDC_MDIO_CTRL1_REG, MDC_MDIO_READ_OP);
	/* step 4. read data from register 25 */
	uint16_t out_data = read_data(phyad, MDC_MDIO_DATA_READ_REG);
	
	return out_data;
}

#define MDC_MDIO_DATA_WRITE_REG 24
#define MDC_MDIO_WRITE_OP 0x0003


void write_data_8367(uint8_t phyad, uint16_t regad, uint16_t out_data)
{
	/* step 1. write address control code to register 31 */
	write_data(phyad, MDC_MDIO_CTRL0_REG, MDC_MDIO_ADDR_OP);
	/* step 2. write address to register 23 */
	write_data(phyad, MDC_MDIO_ADDRESS_REG, regad);
	/* step 3. write read data register 24 */
	write_data(phyad, MDC_MDIO_DATA_WRITE_REG, out_data);
	/* step 3. write read data register 21 */
	write_data(phyad, MDC_MDIO_CTRL1_REG, MDC_MDIO_WRITE_OP);
}


void help(void)
{
	printf("=====================================================================================\r\n");
	
//	printf("\r\n");
//	printf("8367read  <phyAddr|all> <regAddr|all>\r\n");
//	printf("8367write <phyAddr> <regAddr> <value>\r\n");
	printf("init8                            : Init RTL8367RB.\r\n");
	printf("initp                            : Init PHY.\r\n");
	printf("tm<1|2|3|4>                      : 1000Base-T Test mode<1|2|3|4>.\r\n");
	printf("cm                               : 100Base-T Compliance test.\r\n");
	printf("\r\n");
	printf("r8i <regAddr>                    : Read  a value from a RTL8367RB register using iic.\r\n");
	printf("w8i <regAddr> <value>            : Write a value  to  a RTL8367RB register using iic.\r\n");
	printf("\r\n");
	printf("rpi <regAddr>                    : Read  a value from a phy register using iic.\r\n");
	printf("wpi <regAddr> <value>            : Write a value  to  a phy register using iic.\r\n");
	printf("\r\n");
	printf("rpm  <phyAddr|all> <regAddr|all> : Read value(s) from phy register(s) using mdio.\r\n");
	printf("wpm <phyAddr> <regAddr> <value>  : Write a value to a phy register using mdio.\r\n");
	printf("\r\n");
	printf("P<A|B|D|E><0-15> <RESET|SET>       : RESET or SET a GPIO_PIN. e.g. : PD12 RESET\r\n");
	printf("=====================================================================================\r\n");
}


#define SDA_IN()  {GPIOC->CRH&=0XFFFFFF0F;GPIOC->CRH|=8<<4;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFFFF0F;GPIOC->CRH|=3<<4;}

#define MDC_L() HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_RESET)
#define MDC_H() HAL_GPIO_WritePin(MDC_GPIO_Port, MDC_Pin, GPIO_PIN_SET)

#define MDIO_OUT() SDA_OUT()
#define MDIO_IN() SDA_IN()

#define GET_MDIO() HAL_GPIO_ReadPin(MDIO_GPIO_Port, MDIO_Pin)

/* MDIO????bit???,MDIO?????????? */
static void mdio_bb_send_bit(int val)
{
       
    HAL_GPIO_WritePin(MDIO_GPIO_Port, MDIO_Pin, (GPIO_PinState)val);
    delay();
    MDC_L();
    delay();
    MDC_H();
}

static void mdio_bb_send_num(unsigned int value ,int bits)
{
    int i;
    MDIO_OUT();
    
    for(i = bits - 1; i >= 0; i--)
        mdio_bb_send_bit((value >> i) & 1);
}

static int mdio_bb_get_bit(void)
{
    int value;

    delay();
    MDC_L();
    delay();
    MDC_H();
    
    value = GET_MDIO();
    
    return value;
}

static int mdio_bb_get_num(int bits)
{
    int i;
    int ret = 0;
    for(i = bits - 1; i >= 0; i--)
    {
        ret <<= 1;
        ret |= mdio_bb_get_bit(); 
    }

    return ret;
}

uint16_t read_data(uint8_t phy, uint8_t reg)
{
	int ret, i = 0;
	MDIO_OUT();
	for(i = 0; i < 32; i++)
		mdio_bb_send_bit(1);
	
	mdio_bb_send_bit(0);
   mdio_bb_send_bit(1);
	
	mdio_bb_send_bit((2 >> 1) & 1);
  mdio_bb_send_bit((2 >> 0) & 1);
	
	mdio_bb_send_num(phy,5);
  mdio_bb_send_num(reg,5);
	
	MDIO_IN();
	if(mdio_bb_get_bit() != 0)
	{
			/* PHY didn't driver TA low -- flush any bits it may be trying to send*/
			for(i = 0; i < 32; i++)
					mdio_bb_get_bit();
			return 0xFFFF;
	}
	
	ret = mdio_bb_get_num(16);
	
	mdio_bb_get_bit();

	return ret;

}

void write_data(uint8_t phy, uint8_t reg, uint16_t value)
{
	int i = 0;
	MDIO_OUT();
	for(i = 0; i < 32; i++)
		mdio_bb_send_bit(1);
	
	mdio_bb_send_bit(0);
   mdio_bb_send_bit(1);
	
	mdio_bb_send_bit((1 >> 1) & 1);
  mdio_bb_send_bit((1 >> 0) & 1);
	
	mdio_bb_send_num(phy,5);
  mdio_bb_send_num(reg,5);
	
//	MDIO_IN();
//	if(mdio_bb_get_bit() != 0)
//	{
//			/* PHY didn't driver TA low -- flush any bits it may be trying to send*/
//			for(i = 0; i < 32; i++)
//					mdio_bb_get_bit();
//			return 0xFFFF;
//	}

 /*  send the turnaround (10) */  
    mdio_bb_send_bit(1);
    mdio_bb_send_bit(0);
		
		mdio_bb_send_num(value,16);
	
	
//	for(i = 0; i < 32; i++)
		mdio_bb_send_bit(1);
//	ret = mdio_bb_get_num(16);
//	mdio_bb_get_bit();
//	return ret;

}

