/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   Һ����������ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
// //void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
// {
// 	for(; nCount != 0; nCount--);
// }

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	u8 flag;
	u32 i;
	/* ϵͳ��ʱ�� 1us ��ʱ��ʼ�� */
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
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);//���ж�
//	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�
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
		if(str_buffer[0]==frame_headerC)  //�ж���û�ж�ά��
		{
			device.use &= ~0x0C; //�ж�ά�� 
		}
		else
		{
			device.use |= 0x0C;//û�ж�ά��
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
//��ʼʱ��
		Uport_PowerUseTime[0]=(AnsiChardata[12]-'0')*36000;
		Uport_PowerUseTime[0]+=(AnsiChardata[13]-'0')*3600;
		Uport_PowerUseTime[0]+=(AnsiChardata[19]-'0')*600;
		Uport_PowerUseTime[0]+=(AnsiChardata[20]-'0')*60;
		Uport_PowerUseTime[0]+=(AnsiChardata[24]-'0')*10;
		Uport_PowerUseTime[0]+=(AnsiChardata[25]-'0');
		Uport_PowerUseTime[0]= 0;
		Uport_PowerUseTime[1]= Uport_PowerUseTime[0];
 		tft_DisplayStr(52, 0, AnsiChardata,POINT_COLOR, BACK_COLOR,3);
//��ȡ����,�豸��
//Addr_info,��ʽ��0X67 LEN ADDR F0 XX XX (16�ֽ�AD����) (12�ֽ��豸��) CHECK 0X99
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

//�ı�����ʼ		
		for(i=0;i<2048;i++)
		{
		LCD1_TxtBuffer[i] = gImage10_16_288_1bitC[i];
		LCD2_TxtBuffer[i] = gImage10_16_288_1bitC[i];
		}
		LCD1_TxtBuffer[2048]=0;
		LCD1_TxtBuffer[2049]=0;
		LCD2_TxtBuffer[2048]=0;
		LCD2_TxtBuffer[2049]=0;
//��ά���ʼ		
 		tft_Clear(80,56,128,128,BLUE,3);				
			if((device.use&0x04)==0x0) //������ʾ
			{
//				DisplayPROT_EWM(unsigned int x, unsigned int y, u8 num,u8 cs);
				DisplayPROT_EWM(80,56,0,1);
				DisplayPROT_EWM(80,56,1,2);
			}
		Delay_us(100);	
	time_sys = 0;
	while(1)
	{
		if(GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN) ==0)  //����=0,1S������Ϊ��λ
		{
	//		SystemReset();
			
		GPIO_SetBits(SSB0_PORT, SSB0_PIN);
		GPIO_SetBits(SSB1_PORT, SSB1_PIN);
		GPIO_SetBits(SSB2_PORT, SSB2_PIN);
		GPIO_SetBits(SSC0_PORT, SSC0_PIN);
		GPIO_SetBits(SSC1_PORT, SSC1_PIN);
		GPIO_SetBits(SSC2_PORT, SSC2_PIN);
			Delay_us(200);	
		//��ȡ����
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
			FLASH2_GPIOSPI_SER(Addr_info);  ////ÿ�β���4K
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
		
    if(time_sys-check_time >= 5000)			//��ʱ����豸
		{
			check_time += 5000;
//			GPIO_NegationBits(LED_PORT, LED_PIN);
			GPIO_SetBits(LED_PORT, LED_PIN);
//		UART1_Send_Data(UART_BUFFER,16);
// 		AllPort_PowerInfo();
// 			UART_BUFFER[0] = 0x11;	
			
			if((device.use&0x10)==0x10) //��ά���и���
			{
				device.use &= ~0x10; //
				DisplayPROT_EWM(80,56,0,1);
				DisplayPROT_EWM(80,56,1,2);
			}
		}
		
    if(UART1_Error==1)			//������
		{			
			UART1_Error = 0;
		}
		
    if(UART2_Error==1)			//������
		{	
			
		}
		
		uart1_cmd();			
		uart3_cmd();		
		
    if(time_sys-time_s_temp >= 1000)			//ʱ���������
		{
			time_s_temp +=1000;
			time_s++;		
			
//			Dport_ChargeState();
			if((checking_portB&0xF0)==0x40) 
			{
			ChargeCtrl_B();	//�����ϵ�
			}
			if((checking_portC&0xF0)==0x40) 
			{
			ChargeCtrl_C();	//�����ϵ�
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
		
    if(time_sys-time_sys_temp1 >= 1000)			//ʱ���������
		{
			time_sys_temp1 +=1000;
			tft_1bitdeep_TXT (18, 0, LCD1_TxtBuffer,POINT_COLOR, BACK_COLOR,1);
		}
		
		uart1_cmd();			
		uart3_cmd();		
		
    if(time_sys-time_sys_temp2 >= 1000)			//ʱ���������
		{
			time_sys_temp2 +=1000;
			tft_1bitdeep_TXT (18, 0, LCD2_TxtBuffer,POINT_COLOR, BACK_COLOR,2);
//			tft_1bitdeep_TXT (18, 0, LCD2_TxtBuffer,BACK_COLOR,POINT_COLOR, 2);
		}
		
		uart1_cmd();			
		uart3_cmd();
		
    if(time_sys-time_sys_temp3 >= 2000)			//ʱ���������
		{
			time_sys_temp3 +=2000;
			if((time_s-testcmd3_time)>=5)  //0x16 0xe2����ȷ�����ӹ���
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
		checking_portB = 0x00;  //SUB�ÿ�
		}
		
		if(Uport_PowerUseTime[1]>0)
		{
			Dport_ChargeStateC();
		}
		else
		{
		checking_portC = 0x00;  //SUB�ÿ�
		}
		
	}
  

 }

void uart1_cmd (void)
{
		u16 last_i;
		u8 last_d;
	UART1_Receive_Length = UART1_RXBUFFE_LAST - UART1_RXBUFFE_HEAD;
	UART1_Receive_Length &= UART1_RX_MAX;//����ֽ�
/********������ַ���Ϊһ֡���ݵĽ�����ʶ************/
		if(UART1_Receive_Length > 0 )	//ֻ�н��յ�1���������ϲ����ж�
		{
			if(UART1_RXBUFFER[UART1_RXBUFFE_HEAD] == frame_headerC) 	//֡��ʼ��־   
			{
				UART1_RX_State = 1;
				if((UART1_Receive_Length >= 2)&&((UART1_Receive_Pointer[(UART1_RXBUFFE_HEAD+1)&UART1_RX_MAX]<<1) <= UART1_Receive_Length)) 	//���ȸպñ�־   
				{
					UART1_RX_State |= 2;
					last_i = UART1_RXBUFFE_HEAD+(UART1_Receive_Pointer[(UART1_RXBUFFE_HEAD+1)&UART1_RX_MAX]<<1)-1;
					last_i &= UART1_RX_MAX;
					last_d = UART1_Receive_Pointer[last_i];
					if((last_d == frame_last))//У�����
					{
						if((UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+2)&UART1_RX_MAX] ==device.addr) || (UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+2)&UART1_RX_MAX] ==GLOBLE_ADDR)) 
						{			
							switch(UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+4)&UART1_RX_MAX])
							{    		
		//					case 0x51:  cmd_Device_Info();		    break;//��ȡ�豸��Ϣ
							case 0x53:  cmd_Port_Info();		    		break;//��ȡ�˿���Ϣ
							case 0x55:  cmd_Device_Check();		    	break;//�˶���Ϣ
							case 0x57:  cmd_Device_num();		    		break;//�豸��
							case 0x59:  cmd_Power_off();		    		break;//�ϵ�����
							case 0x5a:  cmd_Power_on();		    			break;//�ϵ�����
								
		//          case 0x10:  cmd_Hub_Rst();						break;//��λHUB		 
							case 0x11:  cmd_File_Requst();		    	break;//�ļ���������
							case 0x12:  cmd_File_Tx();		    			break;//�ļ�����
							case 0x13:  cmd_File_Recall();		    	break;//�ļ�����
							case 0x14:  cmd_File_Erase();		    		break;//�ļ�����
							case 0x16:  cmd_ShakeHands();		    break;//����
							case 0x3E:  Device_Rst();   				break;//��λ�豸
								
		//          case 0xE1:  cmd_Get_State();   			break;//��HUB�ŵ�
		//          case 0xE2:  cmd_Set_State();   			break;//����HUB�ŵ�FLASH
							case 0xE3:  cmd_Erase_Flash();      	break;//
							case 0xE4:  cmd_Read_Flash();       	break;//
							case 0xE5:  cmd_Write_Flash();      	break;//						
							case 0xE6:  cmd_Get_ADC();      			break;//						
							case 0xE7:  cmd_Save_ADC();   				break;//����ADC����

							default:	    break;		   	
							}//end switch
						}
						else
						if((UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+2)&UART1_RX_MAX] ==Broadcast)) 
						{
							switch(UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+4)&UART1_RX_MAX])
							{    		
		//          case 0x10:  cmd_Hub_Rst();		    	break;//��λHUB		 
		//					case 0x51:  cmd_device_info();		  break;//��ȡ�豸��Ϣ

							default:	    break;		   	
							}//end switch
						}
					}
					else//У��Բ���
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
				UART1_RXBUFFE_HEAD &= UART1_RX_MAX;//����ֽ�
			}
			else
		if(UART1_RX_State ==0)   //�ȴ��������
			{
// 				UART1_RXBUFFE_HEAD +=0;
// 				UART1_RXBUFFE_HEAD &= UART1_RX_MAX;//����ֽ�
			}
			else
			{
			UART1_RXBUFFE_HEAD += (UART1_RXBUFFER[(UART1_RXBUFFE_HEAD+1)&UART1_RX_MAX]<<1);
		  UART1_RXBUFFE_HEAD &= UART1_RX_MAX;//����ֽ�
			}
 		UART1_RX_State =0;
		}   //len >0
	
} 
void uart3_cmd (void)
{
	UART3_Receive_Length = UART3_RXBUFFE_LAST - UART3_RXBUFFE_HEAD;
	UART3_Receive_Length &= UART3_RX_MAX;//����ֽ�
/********������ַ���Ϊһ֡���ݵĽ�����ʶ************/
		if(UART3_Receive_Length > 0 )	//ֻ�н��յ�1���������ϲ����ж�
		{
			if(UART3_RXBUFFER[UART3_RXBUFFE_HEAD] == frame_headerC) 	//֡��ʼ��־   
			{
				UART3_RX_State = 1;
				
				if((UART3_Receive_Length >= 2)&&((UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+1)&UART3_RX_MAX]) <= (UART3_Receive_Length>>1))) 	//���ȸպñ�־   
				{
				UART3_RX_State |= 2;
				if((UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+2)&UART3_RX_MAX] ==device.addr) || (UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+2)&UART3_RX_MAX] ==GLOBLE_ADDR)) 
				{			
					switch(UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+4)&UART3_RX_MAX])
					{    		
//          case 0x10:  cmd_Hub_Ctrl();		break;//��λ		 
//					case 0x51:  charge_device_info();		    break;//��ȡ�豸��Ϣ
//		  		case 0x16:  Test_device();		    			break;//
					case 0x16:  cmd3_ShakeHands();		    break;//����

          case 0xE1:  cmd3_Get_State();   			break;//��HUB�ŵ�
          case 0xE2:  cmd3_Set_State();   			break;//  ����HUB�ŵ�FLASH
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
						cmd3_Set_State();   		//  ����HUB�ŵ�FLASH
				}
			UART3_RXBUFFE_HEAD += (UART3_RXBUFFER[(UART3_RXBUFFE_HEAD+1)&UART3_RX_MAX]<<1);
		  UART3_RXBUFFE_HEAD &= UART3_RX_MAX;//����ֽ�
			}
		}
		else
		{
				UART3_RX_State = 0;
				UART3_RXBUFFE_HEAD +=1;
				UART3_RXBUFFE_HEAD &= UART3_RX_MAX;//����ֽ�
		}
		
		}
	
} 

/* ------------------------------------------end of file---------------------------------------- */

