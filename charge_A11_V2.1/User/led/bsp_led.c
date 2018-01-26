/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
#define SSB0_PIN			  GPIO_Pin_5
#define SSB0_PORT			  GPIOB
#define SSB1_PIN			  GPIO_Pin_4
#define SSB1_PORT			  GPIOB
#define SSB2_PIN			  GPIO_Pin_7
#define SSB2_PORT			  GPIOB
#define SSC0_PIN			  GPIO_Pin_6
#define SSC0_PORT			  GPIOB
#define SSC1_PIN			  GPIO_Pin_9
#define SSC1_PORT			  GPIOB
#define SSC2_PIN			  GPIO_Pin_8
#define SSC2_PORT			  GPIOB

#define EN_485_PIN			GPIO_Pin_6
#define EN_485_PORT			GPIOA

#define LED_PIN			    GPIO_Pin_8
#define LED_PORT			  GPIOA
#define LED1_PIN			  GPIO_Pin_15
#define LED1_PORT			  GPIOA
#define LED2_PIN			  GPIO_Pin_10
#define LED2_PORT			  GPIOC
#define KEY_PIN			    GPIO_Pin_11 //输入
#define KEY_PORT			  GPIOC

#define RJ45_IO1_PIN			GPIO_Pin_7
#define RJ45_IO1_PORT			GPIOA

#define USB_DB0_PIN			  GPIO_Pin_4
#define USB_DB0_PORT			GPIOC
#define USB_DB1_PIN			  GPIO_Pin_5
#define USB_DB1_PORT			GPIOC
#define USB_DC0_PIN			  GPIO_Pin_0
#define USB_DC0_PORT			GPIOB
#define USB_DC1_PIN			  GPIO_Pin_1
#define USB_DC1_PORT			GPIOB

#define LCD_CS1_PIN			  GPIO_Pin_12
#define LCD_CS1_PORT			GPIOB
#define LCD_CS2_PIN			  GPIO_Pin_5
#define LCD_CS2_PORT			GPIOA
#define SPI_MOSI_PIN			GPIO_Pin_15
#define SPI_MOSI_PORT			GPIOB
#define SPI_MISO_PIN			GPIO_Pin_14  //输入
#define SPI_MISO_PORT			GPIOB
#define SPI_CLK_PIN			  GPIO_Pin_13
#define SPI_CLK_PORT			GPIOB
#define SPI_CS_PIN			  GPIO_Pin_7
#define SPI_CS_PORT			  GPIOC
#define LCD_RS_PIN			  GPIO_Pin_6
#define LCD_RS_PORT			  GPIOC
#define LCD_WR_PIN			  GPIO_Pin_2
#define LCD_WR_PORT			  GPIOD
#define LCD_RD_PIN			  GPIO_Pin_12
#define LCD_RD_PORT			  GPIOC
#define LCD_RST_PIN			  GPIO_Pin_9
#define LCD_RST_PORT			GPIOC
#define LCD_TE_PIN			  GPIO_Pin_8  //输入
#define LCD_TE_PORT			  GPIOC

#define FLASH_CS_PIN			GPIO_Pin_4
#define FLASH_CS_PORT			GPIOA
 */


#include "bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*使能SWD 禁用JTAG*/

		/*开启LED的外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE); 
//-----------输出类----------------
		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*选择要控制的GPIOA组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_15;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/*选择要控制的GPIOB组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
		/*选择要控制的GPIOC组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13;	
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
		
		/*选择要控制的GPIOD组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
		GPIO_Init(GPIOD, &GPIO_InitStructure);	
//-----------输入类----------------
		/*设置引脚模式为通用浮空输入*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		
		/*选择要控制的GPIOA组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);	

/*选择要控制的GPIOB组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
		/*选择要控制的GPIOC组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_11;	
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
		
		/*设置引脚模式为通用浮空输入*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		 
		/*选择要控制的GPIOA组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		/*选择要控制的GPIOC组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
		
		/*设置引脚模式为通用浮空输入*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		/*选择要控制的GPIOA组引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);	

		 
		
		/* 写1*/
//		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		
		/* 写0	*/
//		GPIO_ResetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_13);	 
}

//-------------------------------------------------------------------
void GPIO_NegationBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) //dwgl  取反
{
	  GPIOx->ODR = GPIOx->ODR^GPIO_Pin;
}


/*********************************************END OF FILE**********************/
