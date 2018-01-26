//*******************************************
//dwgl for stm32f1XX
//V1.1 20160401
//*******************************************
#include "stm32f10x.h"

  u8  *DMA1_Channel1_Pointer;
  u8   DMA1_Channel1_State;
  u8   DMA1_Channel1_Error;
  u32  DMA1_Channel1_Buffer;

  u8  *DMA2_Channel1_Pointer;
  u8   DMA2_Channel1_State;
  u8   DMA2_Channel1_Error;
  u32  DMA2_Channel1_Buffer;

//*******************************************
void DMA_Configuration(void)
{
	DMA1_Channel1_Init();
//	DMA2_Channel1_Init();
}
//*******************************************
void DMA1_Channel1_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		
	/* DMA channel1 configuration */
	DMA_DeInit(DMA1_Channel1);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 			//ADC地址
//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	//内存地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_BUFFER;	//内存地址
	
// 		/*方向：从内存到外设*/		
// 		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 320;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址固定
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  				//内存地址固定
// 		/*内存地址自增*/
 		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;										//循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	/* Enable DMA channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
//	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断
}
//*******************************************
void DMA2_Channel1_Init(void)
{
	
}
//*******************************************
void DMA1_Channel1_IRQHandler(void)
{
//DMA1_Channel1_IRQn
	DMA1_Channel1_State = 1;
	ADC1_State |= 1;
	DMA_ClearFlag(DMA1_FLAG_GL1);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, DISABLE);
	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
//	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
	
	GPIOC->ODR ^= GPIO_Pin_3; 
}
