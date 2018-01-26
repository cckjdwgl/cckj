#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_3)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			{p->BSRR=i;}			//设置为高电平		
#define digitalLo(p,i)			{p->BRR=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_0)
#define LED1_OFF		digitalHi(GPIOB,GPIO_Pin_0)
#define LED1_ON			digitalLo(GPIOB,GPIO_Pin_0)
//MOS ON/OFF
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

#define AIN1_PIN			  GPIO_Pin_3
#define AIN1_PORT			  GPIOC
#define AIN2_PIN			  GPIO_Pin_2
#define AIN2_PORT			  GPIOC
#define AIN3_PIN			  GPIO_Pin_0
#define AIN3_PORT			  GPIOA
#define AIN4_PIN			  GPIO_Pin_1
#define AIN4_PORT			  GPIOA
#define AIN5_PIN			  GPIO_Pin_3
#define AIN5_PORT			  GPIOA
#define AIN6_PIN			  GPIO_Pin_2
#define AIN6_PORT			  GPIOA
#define AIN7_PIN			  GPIO_Pin_1
#define AIN7_PORT			  GPIOC
#define AIN8_PIN			  GPIO_Pin_0
#define AIN8_PORT			  GPIOC


#define EN_485_PIN			GPIO_Pin_6
#define EN_485_PORT			GPIOA

#define LED_PIN			    GPIO_Pin_8
#define LED_PORT			  GPIOA
#define LED1_PIN			  GPIO_Pin_15
#define LED1_PORT			  GPIOA
#define LED2_PIN			  GPIO_Pin_10
#define LED2_PORT			  GPIOC
#define KEY_PIN			    GPIO_Pin_11
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

#define DPB1_PIN			   GPIO_Pin_12
#define DPB1_PORT			   GPIOA
#define DPC3_PIN			   GPIO_Pin_11
#define DPC3_PORT			   GPIOA

#define LCD_CS1_PIN			  GPIO_Pin_12
#define LCD_CS1_PORT			GPIOB
#define LCD_CS2_PIN			  GPIO_Pin_5
#define LCD_CS2_PORT			GPIOA
#define SPI2_MOSI_PIN			GPIO_Pin_15
#define SPI2_MOSI_PORT			GPIOB
#define SPI2_MISO_PIN			GPIO_Pin_14
#define SPI2_MISO_PORT			GPIOB
#define SPI2_CLK_PIN			  GPIO_Pin_13
#define SPI2_CLK_PORT			GPIOB
#define SPI2_CS_PIN			  GPIO_Pin_7
#define SPI2_CS_PORT			  GPIOC
#define LCD_RS_PIN			  GPIO_Pin_6
#define LCD_RS_PORT			  GPIOC
#define LCD_WR_PIN			  GPIO_Pin_2
#define LCD_WR_PORT			  GPIOD
#define LCD_RD_PIN			  GPIO_Pin_12
#define LCD_RD_PORT			  GPIOC
#define LCD_RST_PIN			  GPIO_Pin_9
#define LCD_RST_PORT			GPIOC
#define LCD_TE_PIN			  GPIO_Pin_8
#define LCD_TE_PORT			  GPIOC

// #define FLASH_CS_PIN			GPIO_Pin_4
// #define FLASH_CS_PORT			GPIOA
#define FLASH_CS_PIN			GPIO_Pin_13
#define FLASH_CS_PORT			GPIOC


void LED_GPIO_Config(void);
void GPIO_NegationBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); //dwgl  取反


#endif /* __LED_H */
