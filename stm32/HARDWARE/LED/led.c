#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//********************************************************************************

//LED��������	 

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com	

//LED_D1 --  ��Դָʾ��--��������
//LED_D2 --  PA1	 --�͵�ƽ����   


//********************************************************************************								  
////////////////////////////////////////////////////////////////////////////////// 	   


//LED_D2 --  PA1	��ʼ��


void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ�� LED_D2 --  PA1 �˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 			 //LED_D2 --  PA1 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);									 //�����趨������ʼ��PA1

	GPIO_SetBits(GPIOA,GPIO_Pin_1);						             //PA1 �����-- ״̬ --LED����

	
}



































//********************************************************************************

//LED��������	 

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com	

//********************************************************************************	
 
