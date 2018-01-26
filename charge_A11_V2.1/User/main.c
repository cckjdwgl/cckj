/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   液晶触摸画板实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
// //void Delay(__IO uint32_t nCount)	 //简单的延时函数
// {
// 	for(; nCount != 0; nCount--);
// }

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	u8 flag;
	u32 i;
	/* 系统定时器 1us 定时初始化 */
  SysTick_Init();
//	CPU_CRITICAL_ENTER();
  LED_GPIO_Config();	
	GPIO_ResetBits(LED_PORT, LED_PIN);
	ADC_Configuration();
//	DAC_Configuration();
	UART_Configuration();
//	SPI_Configuration();
//	DMA_Configuration();
	
	NVIC_Configuration();
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);//开中断
//	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断
//	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

//	CPU_CRITICAL_EXIT();
	step =0;
	time_s = 0;
	time_sys = 0;
	check_time = time_sys;
	device.TASK_state =0x00;
//	ADC_Cmd(ADC1, ENABLE);
		Delay_us(150);	
		GPIO_NegationBits(LED_PORT, LED_PIN);
		Delay_us(150);	
		GPIO_NegationBits(LED_PORT, LED_PIN);
		Delay_us(150);	
		GPIO_NegationBits(LED_PORT, LED_PIN);
		Delay_us(150);	
		GPIO_NegationBits(LED_PORT, LED_PIN);
		Delay_us(150);	
		GPIO_NegationBits(LED_PORT, LED_PIN);
		Delay_us(150);	
		GPIO_NegationBits(LED_PORT, LED_PIN);
		
		FLASH2_GPIOSPI_Read (0, str_buffer, 128);
		if(str_buffer[0]==frame_headerC)  //判断有没有二维码
		{
			device.use &= ~0x0C; //有二维码 
		}
		else
		{
			device.use |= 0x0C;//没有二维码
		}
			
				
// 		Addr_Set();
//		hub_id_info();
		GPIO_SetBits(SSB0_PORT, SSB0_PIN);
		GPIO_SetBits(SSB1_PORT, SSB1_PIN);
		GPIO_SetBits(SSB2_PORT, SSB2_PIN);
		GPIO_SetBits(SSC0_PORT, SSC0_PIN);
		GPIO_SetBits(SSC1_PORT, SSC1_PIN);
		GPIO_SetBits(SSC2_PORT, SSC2_PIN);
		
		GPIO_ResetBits(RJ45_IO1_PORT, RJ45_IO1_PIN);
		GPIO_ResetBits(EN_485_PORT, EN_485_PIN);
//		GPIO_SetBits(RJ45_IO1_PORT, RJ45_IO1_PIN);
		
		
 	GPIO_ResetBits(LCD_RST_PORT, LCD_RST_PIN);
		LCD_Init();	
		LCD_Init1();	
 	GPIO_ResetBits(LCD_CS1_PORT, LCD_CS1_PIN);
 	GPIO_ResetBits(LCD_CS2_PORT, LCD_CS2_PIN);
		LCD_Clear(RED);
		LCD_Clear(GREEN);
		LCD_Clear(BLUE);
//				tft_16bitdeep_array(0,0,80,240,gImage5_240_80_16bitC);
				tft_16bitdeep_BMP (220,0,gImage11_240_100_16bitC);		
 	GPIO_SetBits(LCD_CS1_PORT, LCD_CS1_PIN);
 	GPIO_SetBits(LCD_CS2_PORT, LCD_CS2_PIN);
	
		tft_Clear(34,0,196,240,BLUE,3);	
		
		tft_1bitdeep_BMP (80,56,gImage12_128_128_1bitC,0xffff,0x0000,3);
				
		LCD_DrawPoint(0,0);
		LCD_DrawPoint(100,0);
//初始时间
		Uport_PowerUseTime[0]=(AnsiChardata[12]-'0')*36000;
		Uport_PowerUseTime[0]+=(AnsiChardata[13]-'0')*3600;
		Uport_PowerUseTime[0]+=(AnsiChardata[19]-'0')*600;
		Uport_PowerUseTime[0]+=(AnsiChardata[20]-'0')*60;
		Uport_PowerUseTime[0]+=(AnsiChardata[24]-'0')*10;
		Uport_PowerUseTime[0]+=(AnsiChardata[25]-'0');
		Uport_PowerUseTime[0]= 0;
		Uport_PowerUseTime[1]= Uport_PowerUseTime[0];
 		tft_DisplayStr(52, 0, AnsiChardata,POINT_COLOR, BACK_COLOR,3);
//获取基线,设备号
//Addr_info,格式：0X67 LEN ADDR F0 XX XX (16字节AD基线) (12字节设备号) CHECK 0X99
		FLASH2_GPIOSPI_Read (Addr_info, (u8*)ADC_Base0, 16);
//  		DisplayADC_BL(150, 0, ADC_Base0,POINT_COLOR, BACK_COLOR,1);
//  		DisplayADC_BL(150, 0, &ADC_Base0[3],POINT_COLOR, BACK_COLOR,2);
//  		DisplayADC_BL(150, 0, &ADC_Base0[5],POINT_COLOR, BACK_COLOR,3);

		FLASH2_GPIOSPI_Read (Addr_info1, str_buffer, 64);
		if(str_buffer[0]==frame_headerC)
		{
			for(i=0;i<12;i++)
			{
				device_num[i]= str_buffer[5+i];
			}
				device_num[i++]= ' ';
				device_num[i++]= 0;
		}
		else
		{
			for(i=0;i<12;i++)
			{
				device_num[i]= '?';
			}
				device_num[i++]= ' ';
				device_num[i++]= 0;
		}
	//	tft_DisplayStr(270, 125, device_num,0x0000,0xffff,3);
		tft_DisplayStr(300, 125, device_num,0x0000,0xffff,3);

//文本区初始		
		for(i=0;i<2048;i++)
		{
		LCD1_TxtBuffer[i] = gImage10_16_288_1bitC[i];
		LCD2_TxtBuffer[i] = gImage10_16_288_1bitC[i];
		}
		LCD1_TxtBuffer[2048]=0;
		LCD1_TxtBuffer[2049]=0;
		LCD2_TxtBuffer[2048]=0;
		LCD2_TxtBuffer[2049]=0;
//二维码初始		
 		tft_Clear(80,56,128,128,BLUE,3);				
			if((device.use&0x04)==0x0) //有码显示
			{
//				DisplayPROT_EWM(unsigned int x, unsigned int y, u8 num,u8 cs);
				DisplayPROT_EWM(80,56,0,1);
				DisplayPROT_EWM(80,56,1,2);
			}
		Delay_us(100);	
	time_sys = 0;
	while(1)
	{
		if(GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN) ==0)  //按键=0,1S进行人为复位
		{
	//		SystemReset();
			
		GPIO_SetBits(SSB0_PORT, SSB0_PIN);
		GPIO_SetBits(SSB1_PORT, SSB1_PIN);
		GPIO_SetBits(SSB2_PORT, SSB2_PIN);
		GPIO_SetBits(SSC0_PORT, SSC0_PIN);
		GPIO_SetBits(SSC1_PORT, SSC1_PIN);
		GPIO_SetBits(SSC2_PORT, SSC2_PIN);
			Delay_us(200);	
		//获取基线
			Get_ADC_BaseLine();
			FLASH2_GPIOSPI_Read (Addr_info, (u8*)global_u16BUFFER, 16);
// 			flag = 0;
// 			for(i=0;i<16;i++)
// 			{
// 				if((ADC_Base0[i]- global_u16BUFFER[i]>32)&&(global_u16BUFFER[i]-ADC_Base0[i]>32))
// 				{
// 					flag = 1;
// 				}
// 			}
// 			if(flag == 1)
			{
			flag = 0;
			FLASH2_GPIOSPI_SER(Addr_info);  ////每次擦擦4K
			FLASH2_GPIOSPI_Write(Addr_info, (u8*)ADC_Base0, 16);
			FLASH2_GPIOSPI_Read (Addr_info, (u8*)global_u16BUFFER, 16);
			i=100000;
			while(i--)
			{
				GPIO_SetBits(LED_PORT, LED_PIN);
			}
			
			}
			
			NVIC_SystemReset();
		}		
		
		uart1_cmd();			
		uart3_cmd();		
		
    if(time_sys-check_time >= 5000)			//定时检测设备
		{
			check_time += 5000;
//			GPIO_NegationBits(LED_PORT, LED_PIN);
			GPIO_SetBits(LED_PORT, LED_PIN);
//		UART1_Send_Data(UART_BUFFER,16);
// 		AllPort_PowerInfo();
// 			UART_BUFFER[0] = 0x11;	
			
			if((device.use&0x10)==0x10) //二维码有更新
			{
				device.use &= ~0x10; //
				DisplayPROT_EWM(80,56,0,1);
				DisplayPROT_EWM(80,56,1,2);
			}
		}
		
    if(UART1_Error==1)			//接收满
		{			
			UART1_Error = 0;
		}
		
    if(UART2_Error==1)			//接收满
		{	
			
		}
		
		uart1_cmd();			
		uart3_cmd();		
		
    if(time_sys-time_s_temp >= 1000)			//时间控制任务
		{
			time_s_temp +=1000;
			time_s++;		
			
//			Dport_ChargeState();
			if((checking_portB&0xF0)==0x40) 
			{
			ChargeCtrl_B();	//互拆上电
			}
			if((checking_portC&0xF0)==0x40) 
			{
			ChargeCtrl_C();	//互拆上电
			}
			for(i=0;i<3;i++)
				{
					UART_BUFFER[i] = Dport_State[i]+'0';
				}
				UART_BUFFER[i] =0;
 			tft_DisplayStr(170, 0, UART_BUFFER,POINT_COLOR, BACK_COLOR,1);
			for(i=0;i<3;i++)
				{
					UART_BUFFER[i] = Dport_State[3+i]+'0';
				}
				UART_BUFFER[i] =0;
 			tft_DisplayStr(170, 0, UART_BUFFER,POINT_COLOR, BACK_COLOR,2);
			
			AnsiChardata[12] = Uport_PowerUseTime[0]/36000+'0';
			AnsiChardata[13] = Uport_PowerUseTime[0]%36000/3600+'0';
			AnsiChardata[19] = Uport_PowerUseTime[0]%3600/600+'0';
			AnsiChardata[20] = Uport_PowerUseTime[0]%600/60+'0';
			AnsiChardata[24] = Uport_PowerUseTime[0]%60/10+'0';
			AnsiChardata[25] = Uport_PowerUseTime[0]%10+'0';
			for(i=0;i<2;i++)
				{
					UART_BUFFER[i] = AnsiChardata[12+i];
				}
				UART_BUFFER[i] =0;
			tft_DisplayStr(52, 96, UART_BUFFER,POINT_COLOR, BACK_COLOR,1);
			for(i=0;i<2;i++)
				{
					UART_BUFFER[i] = AnsiChardata[19+i];
				}
				UART_BUFFER[i] =0;
			tft_DisplayStr(52, 152, UART_BUFFER,POINT_COLOR, BACK_COLOR,1);
			for(i=0;i<2;i++)
				{
					UART_BUFFER[i] = AnsiChardata[24+i];
				}
				UART_BUFFER[i] =0;
			tft_DisplayStr(52, 192, UART_BUFFER,POINT_COLOR, BACK_COLOR,1);
				
			if(Uport_PowerUseTime[0]>0)
			{
			Uport_PowerUseTime[0]--;
			GPIO_SetBits(LED1_PORT, LED1_PIN);				
			}
			else
			{
			GPIO_ResetBits(LED1_PORT, LED1_PIN);
			Dport_ChargeOFF(0);
			Dport_ChargeOFF(1);
			Dport_ChargeOFF(2);
			Dport_State[0] = 0;
			Dport_State[1] = 0;
			Dport_State[2] = 0;
			}
			
			
			AnsiChardata[12] = Uport_PowerUseTime[1]/36000+'0';
			AnsiChardata[13] = Uport_PowerUseTime[1]%36000/3600+'0';
			AnsiChardata[19] = Uport_PowerUseTime[1]%3600/600+'0';
			AnsiChardata[20] = Uport_PowerUseTime[1]%600/60+'0';
			AnsiChardata[24] = Uport_PowerUseTime[1]%60/10+'0';
			AnsiChardata[25] = Uport_PowerUseTime[1]%10+'0';
			for(i=0;i<2;i++)
				{
					UART_BUFFER[i] = AnsiChardata[12+i];
				}
				UART_BUFFER[i] =0;
			tft_DisplayStr(52, 96, UART_BUFFER,POINT_COLOR, BACK_COLOR,2);
			for(i=0;i<2;i++)
				{
					UART_BUFFER[i] = AnsiChardata[19+i];
				}
				UART_BUFFER[i] =0;
			tft_DisplayStr(52, 152, UART_BUFFER,POINT_COLOR, BACK_COLOR,2);
			for(i=0;i<2;i++)
				{
					UART_BUFFER[i] = AnsiChardata[24+i];
				}
				UART_BUFFER[i] =0;
			tft_DisplayStr(52, 192, UART_BUFFER,POINT_COLOR, BACK_COLOR,2);
			
			if(Uport_PowerUseTime[1]>0)
			{				
			GPIO_SetBits(LED2_PORT, LED2_PIN);
			Uport_PowerUseTime[1]--;
			}
			else
			{
			GPIO_ResetBits(LED2_PORT, LED2_PIN);
			Dport_ChargeOFF(3);
			Dport_ChargeOFF(4);
			Dport_ChargeOFF(5);
			Dport_State[3] = 0;
			Dport_State[4] = 0;
			Dport_State[5] = 0;
			}
			
		}
		
		uart1_cmd();			
		uart3_cmd();		
		
    if(time_sys-time_sys_temp1 >= 1000)			//时间控制任务
		{
			time_sys_temp1 +=1000;
			tft_1bitdeep_TXT (18, 0, LCD1_TxtBuffer,POINT_COLOR, BACK_COLOR,1);
		}
		
		uart1_cmd();			
		uart3_cmd();		
		
    if(time_sys-time_sys_temp2 >= 1000)			//时间控制任务
		{
			time_sys_temp2 +=1000;
			tft_1bitdeep_TXT (18, 0, LCD2_TxtBuffer,POINT_COLOR, BACK_COLOR,2);
//			tft_1bitdeep_TXT (18, 0, LCD2_TxtBuffer,BACK_COLOR,POINT_COLOR, 2);
		}
		
		uart1_cmd();			
		uart3_cmd();
		
    if(time_sys-time_sys_temp3 >= 2000)			//时间控制任务
		{
			time_sys_temp3 +=2000;
			if((time_s-testcmd3_time)>=5)  //0x16 0xe2都有确认连接功能
			{
				UART_BUFFER[0] = 'U';
				UART_BUFFER[1] = 'n';
				UART_BUFFER[2] = 'l';
				UART_BUFFER[3] = 'i';
				UART_BUFFER[4] = 'n';
				UART_BUFFER[5] = 'k';
				UART_BUFFER[6] = 0;
				tft_DisplayStr(190, 0, UART_BUFFER,POINT_COLOR, BACK_COLOR,3);
				GPIO_ResetBits(RJ45_IO1_PORT, RJ45_IO1_PIN);
			}
			else
			{
				UART_BUFFER[0] = 'L';
				UART_BUFFER[1] = 'i';
				UART_BUFFER[2] = 'n';
				UART_BUFFER[3] = 'k';
				UART_BUFFER[4] = 'e';
				UART_BUFFER[5] = 'd';
				UART_BUFFER[6] = 0;
				tft_DisplayStr(190, 0, UART_BUFFER,POINT_COLOR, BACK_COLOR,3);
			}
		}
		
		if(Uport_PowerUseTime[0]>0)
		{
			Dport_ChargeStateB();
		}
		else
		{
		checking_portB = 0x00;  //SUB置空
		}
		
		if(Uport_PowerUseTime[1]>0)
		{
			Dport_ChargeStateC();
		}
		else
		{
		checking_portC = 0x00;  //SUB置空
		}
		
	}
  

 }

void uart1_cmd (void)
{
		u16 last_i;
		u8 last_d;
	UART1_Receive_Length = UART1_RXBUFFE_LAST - UART1_RXBUFFE_HEAD;
	UART1_Receive_Length &= UART1_RX_MAX;//最大字节
/********定义的字符作为一帧数据的结束标识************/
		if(UART1_Receive_Length > 0 )	//只有接收到1个数据以上才做判断
		{
			if(UART1_RXBUFFER[UART1_RXBUFFE_HEAD] == frame_headerC) 	//帧起始标志   
			{
				UART1_RX_State = 1;
				if((UART1_Receive_Length >= 2)&&((UART1_Receive_Pointer[(UART1_RXBUFFE_HEAD+1)&UART1_RX_MAX]<<1) <= UART1_Receive_Length)) 	//长度刚好标志   
				{
					UART1_RX_State |= 2;
					last_i = UART1_RXBUFFE_HEAD+(UART1_Receive_Pointer[(UART1_RXBUFFE_HEAD+1)&UART1_RX_MAX]<<1)-1;
					last_i &= UART1_RX_MAX;
					last_d = UART1_Receive_Pointer[last_i];
					if((last_d == frame_last))//校验对上
					{
						if((UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+2)&UART1_RX_MAX] ==device.addr) || (UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+2)&UART1_RX_MAX] ==GLOBLE_ADDR)) 
						{			
							switch(UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+4)&UART1_RX_MAX])
							{    		
		//					case 0x51:  cmd_Device_Info();		    break;//获取设备信息
							case 0x53:  cmd_Port_Info();		    		break;//获取端口信息
							case 0x55:  cmd_Device_Check();		    	break;//核对信息
							case 0x57:  cmd_Device_num();		    		break;//设备号
							case 0x59:  cmd_Power_off();		    		break;//断电命令
							case 0x5a:  cmd_Power_on();		    			break;//上电命令
								
		//          case 0x10:  cmd_Hub_Rst();						break;//复位HUB		 
							case 0x11:  cmd_File_Requst();		    	break;//文件操作请求
							case 0x12:  cmd_File_Tx();		    			break;//文件传输
							case 0x13:  cmd_File_Recall();		    	break;//文件调用
							case 0x14:  cmd_File_Erase();		    		break;//文件擦除
							case 0x16:  cmd_ShakeHands();		    break;//握手
							case 0x3E:  Device_Rst();   				break;//复位设备
								
		//          case 0xE1:  cmd_Get_State();   			break;//读HUB号到
		//          case 0xE2:  cmd_Set_State();   			break;//设置HUB号到FLASH
							case 0xE3:  cmd_Erase_Flash();      	break;//
							case 0xE4:  cmd_Read_Flash();       	break;//
							case 0xE5:  cmd_Write_Flash();      	break;//						
							case 0xE6:  cmd_Get_ADC();      			break;//						
							case 0xE7:  cmd_Save_ADC();   				break;//保存ADC基线

							default:	    break;		   	
							}//end switch
						}
						else
						if((UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+2)&UART1_RX_MAX] ==Broadcast)) 
						{
							switch(UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+4)&UART1_RX_MAX])
							{    		
		//          case 0x10:  cmd_Hub_Rst();		    	break;//复位HUB		 
		//					case 0x51:  cmd_device_info();		  break;//获取设备信息

							default:	    break;		   	
							}//end switch
						}
					}
					else//校验对不上
					{
						UART1_RX_State |= 0xe0;
					}
				}						
				else
				{
					if( (time_sys -time_uart1)>100 )
					{
					UART1_RX_State |= 0xe0;						
//					BUS_Error_Byte(0x11);
					}
					else
					{
					UART1_RX_State = 0x00;
					}
				}
			
		}
		else
		{
				UART1_RX_State |= 0xe0;
		}
		
		if((UART1_RX_State &0xe0)== 0xe0)	
			{
				UART1_RXBUFFE_HEAD +=1;
				UART1_RXBUFFE_HEAD &= UART1_RX_MAX;//最大字节
			}
			else
		if(UART1_RX_State ==0)   //等待接收完成
			{
// 				UART1_RXBUFFE_HEAD +=0;
// 				UART1_RXBUFFE_HEAD &= UART1_RX_MAX;//最大字节
			}
			else
			{
			UART1_RXBUFFE_HEAD += (UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+1)&UART1_RX_MAX]<<1);
		  UART1_RXBUFFE_HEAD &= UART1_RX_MAX;//最大字节
			}
 		UART1_RX_State =0;
		}   //len >0
	
} 
void uart3_cmd (void)
{
	UART3_Receive_Length = UART3_RXBUFFE_LAST - UART3_RXBUFFE_HEAD;
	UART3_Receive_Length &= UART3_RX_MAX;//最大字节
/********定义的字符作为一帧数据的结束标识************/
		if(UART3_Receive_Length > 0 )	//只有接收到1个数据以上才做判断
		{
			if(UART3_RXBUFFER[UART3_RXBUFFE_HEAD] == frame_headerC) 	//帧起始标志   
			{
				UART3_RX_State = 1;
				
				if((UART3_Receive_Length >= 2)&&((UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+1)&UART3_RX_MAX]) <= (UART3_Receive_Length>>1))) 	//长度刚好标志   
				{
				UART3_RX_State |= 2;
				if((UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+2)&UART3_RX_MAX] ==device.addr) || (UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+2)&UART3_RX_MAX] ==GLOBLE_ADDR)) 
				{			
					switch(UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+4)&UART3_RX_MAX])
					{    		
//          case 0x10:  cmd_Hub_Ctrl();		break;//复位		 
//					case 0x51:  charge_device_info();		    break;//获取设备信息
//		  		case 0x16:  Test_device();		    			break;//
					case 0x16:  cmd3_ShakeHands();		    break;//握手

          case 0xE1:  cmd3_Get_State();   			break;//读HUB号到
          case 0xE2:  cmd3_Set_State();   			break;//  设置HUB号到FLASH
//          case 0xE3:  cmd_Erase_Flash();      break;//
//          case 0xE4:  cmd_Read_Flash();       break;//
//          case 0xE5:  cmd_Write_Flash();      break;//

					default:	    break;		   	
					}//end switch
				}
				else
				if((UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+4)&UART3_RX_MAX] ==0xe2)) 
				{
//          case 0xE2:  
						cmd3_Set_State();   		//  设置HUB号到FLASH
				}
			UART3_RXBUFFE_HEAD += (UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+1)&UART3_RX_MAX]<<1);
		  UART3_RXBUFFE_HEAD &= UART3_RX_MAX;//最大字节
			}
		}
		else
		{
				UART3_RX_State = 0;
				UART3_RXBUFFE_HEAD +=1;
				UART3_RXBUFFE_HEAD &= UART3_RX_MAX;//最大字节
		}
		
		}
	
} 

/* ------------------------------------------end of file---------------------------------------- */

