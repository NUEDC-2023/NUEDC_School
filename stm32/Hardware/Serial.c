#include "stm32f10x.h"                  // Device header
#include "OpenmvComm.h"
#include "OLED.h"
#include "Serial.h"
uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Gyroscope_Init(void)   //陀螺仪的 串口  32's  PA9 is TX, PA10 is RX
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

//usart1 中断服务函数
int counter;
unsigned char Re_buf[11],temp_buf[11];
unsigned char sign,t,he;
static unsigned char Temp[11];

void USART1_IRQHandler(void) 
	{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);  
				//Usart_SendByte(UART8,Usart6_Rx);

					Temp[counter] = USART_ReceiveData(USART1);   
								//Usart_SendByte(UART8,Temp[counter]);

					//??????
					//if(counter == 0 && Re_buf[0] != 0x55) return;      //
				if(counter == 0 && Temp[0] != 0x55) return;      //?
					counter++; 
					if(counter==11) //??? 11 ???
					{ 
						 memcpy(Re_buf,Temp,11);
						 counter=0; 
						 sign=1;
					}
    }
}



float a[3],w[3],angle[3],T;
float fAcc[3], fGyro[3], fAngle[3];
float ring=0;
float ring2=0;
float pitch,roll,yaw;
float pitch2,roll2,yaw2;
float pitch_holder;
float yaw_holder;
float roll_holder;

//转圈圈函数
void ring_check_holder(void)
{
		static float roll_holder_last;
	 if(roll_holder_last>=1200&&roll2<=-1020)ring2++;
   if(roll_holder_last<=-1200&&roll2>=1200)ring2--;
   roll_holder_last=roll2;
}


//
void  Gyroscope_Date(void)
{
   if(sign)
      {
         memcpy(Temp,Re_buf,11);
         sign=0;
         if(Re_buf[0]==0x55)       //检查帧头
         {
            switch(Re_buf[1])
            {
               case 0x51: //这个包是加速度包
                  a[0] = ((short)(Temp[3]<<8 | Temp[2]))/32768.0*16;      //X轴加速度
                  a[1] = ((short)(Temp[5]<<8 | Temp[4]))/32768.0*16;      //Y轴加速度
                  a[2] = ((short)(Temp[7]<<8 | Temp[6]))/32768.0*16;      //Z轴加速度
                  T    = ((short)(Temp[9]<<8 | Temp[8]))/340.0+36.25;      //温度
                  break;
               case 0x52: //标识这个包是角速度包
                  w[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*2000;     //X轴角速度
                  w[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*2000;      //Y轴角速度
                  w[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*2000;      //Z轴角速度
                  T    = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;      //温度
                  break;
               case 0x53: //标识这个包是角度包
                  angle[0] = ((short)(Temp[3]<<8| Temp[2]))/32768.0*180;   //X轴滚转角
                  angle[1] = ((short)(Temp[5]<<8| Temp[4]))/32768.0*180;   //Y轴滚转角
                  angle[2] = ((short)(Temp[7]<<8| Temp[6]))/32768.0*180;   //Z轴偏航角
                  T        = ((short)(Temp[9]<<8| Temp[8]))/340.0+36.25;   //温度
                  //printf("X轴角度:%.2f   Y轴角度:%.2f   Z轴角度:%.2f\r\n",angle[0],angle[1],angle[2]);
                  break;
               default:  break;
            }
						pitch_holder=-10*angle[1];//角度
						yaw_holder=10*angle[0];//航向角度，只需要用这个
						roll2=10*angle[2];//航向角
						ring_check_holder();//数据处理
						roll_holder=roll2+3600*ring2;
			//printf("X??:%.2f  Y??:%.2f  Z??:%.2f  X??:%.2f  Y??:%.2f  Z??:%.2f\r\n",angle[0],angle[1],angle[2],w[0],w[1],w[2]);
         }
      }
      //OLED_ShowBinNum(3,1,pitch_holder*10,4);
	    OLED_ShowSignedNum(4,1,yaw_holder*10,3);
}



//以下为openmv的串口通信部分
//STM32 的PD5为TX 和PD6为RX  (需要重定义功能) ----openmv    5，6都是usart2   
void Serial_Openmv_Init(void)   //Opemmv 的串口
{
	//USART,PD5-TX,PD6-RX
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  //TX 
  GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed    = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD,&GPIO_InitStructure);    
  //RX 
  GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD,&GPIO_InitStructure);
  NVIC_InitTypeDef NVIC_InitStructure;     //串口中断配置结构体变量
	//USART1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      					                
  NVIC_Init(&NVIC_InitStructure);	                        
  //USART 初始化配置
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);                     
	USART_ClearFlag(USART2, USART_FLAG_TC);    
}

uint8_t _Cx=0;  //This is not where Cx is declared as global variable! _Cx for temporary usage.
int RxState = 0;	
//USART2 全局中断服务函数 - openMV RX reading opration included for now, bit shitpile here, lack one layer of implementation(OpenMV_Comm.c).
void USART2_IRQHandler(void)			 
{
		uint8_t com_data; 
		uint8_t i;
		static uint8_t RxCounter1=0;
		static uint8_t RxBuffer1[10]={0};
		static uint8_t RxFlag1 = 0;

		if( USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  	//接受中断
		{
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //清除中断标志
				com_data = USART_ReceiveData(USART2);
			
				if(RxState==0&&com_data==0x86)   //0x2c帧头
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
				else if(RxState==1)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=5||com_data == 0x54)       //RxBuffer1接受满了，接受数据结束
					{
						RxState=2;
						RxFlag1=1;
						_Cx=RxBuffer1[1];
						Cy=RxBuffer1[2]|(RxBuffer1[3]<<8);
					}
				}
				else if(RxState==2)		
				{
						if(RxBuffer1[RxCounter1-1] == 0x54)
						{
									USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);
									if(RxFlag1)
									{
										OpenMV_On_Recieve(_Cx, Cy);
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									for(i=0;i<5;i++)
									{
											RxBuffer1[i]=0x00;      //将存放数据数组清零
									}
									USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
						}
						else   //接受错误
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<5;i++)
									{
											RxBuffer1[i]=0x00;      //将存放数据数组清零
									}
						}
				}
				else   //接受异常
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据组清零
						}
				}

		}
		
}


void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

void USART11_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
