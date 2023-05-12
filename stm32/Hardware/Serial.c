#include "stm32f10x.h"                  // Device header
#include "OpenmvComm.h"

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Gyroscope_Init(void)   //�����ǵ� ����  32's  PA9 is TX, PA10 is RX
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






//STM32 ��PD5ΪTX ��PD6ΪRX  (��Ҫ�ض��幦��) ----openmv    5��6����usart2   
void Serial_Openmv_Init(void)   //Opemmv �Ĵ���
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
  NVIC_InitTypeDef NVIC_InitStructure;     //�����ж����ýṹ�����
	//USART1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      					                
  NVIC_Init(&NVIC_InitStructure);	                        
  //USART ��ʼ������
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

int Cy;
uint8_t Cx=0;
int RxState = 0;	
//USART2 ȫ���жϷ����� - openMV RX reading opration included for now, bit shitpile here, lack one layer of implementation(OpenMV_Comm.c).
void USART2_IRQHandler(void)			 
{
		uint8_t com_data; 
		uint8_t i;
		static uint8_t RxCounter1=0;
		static uint8_t RxBuffer1[10]={0};
		static uint8_t RxFlag1 = 0;

		if( USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)  	//�����ж�
		{
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //����жϱ�־
				com_data = USART_ReceiveData(USART2);
			
				if(RxState==0&&com_data==0x86)   //0x2c֡ͷ
				{
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
				else if(RxState==1)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=5||com_data == 0x54)       //RxBuffer1�������ˣ��������ݽ���
					{
						RxState=2;
						RxFlag1=1;
						Cx=RxBuffer1[1];
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
										OpenMV_On_Recieve(Cx, Cy);
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									for(i=0;i<5;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
									USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
						}
						else   //���ܴ���
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<5;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				}
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //���������������
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

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}