#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"


//////////////////////////////////////////////////////////////////////////////////	 

//�ⲿ�ж� ��������	   

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			


//////////////////////////////////////////////////////////////////////////////////   


//********************************************************************************

// ��ʼ���ⲿ�ж� 

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			

//********************************************************************************
void EXTIX_Init(void)
{
 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

   //PE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

////  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
////  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
////  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

////   //PE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
////  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
////	
////  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
////	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
////  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //K2  -- PC13   �ж����Լ��жϳ�ʼ������  �½��ش���	//K2   ���� --���º󣬵͵�ƽ   
	 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
		
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //�½��ش����ж�
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   //K1  -- PA0        K1 �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;                  //K1  -- PA0 
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    //�����ش����ж�
  	EXTI_Init(&EXTI_InitStructure);														//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���  K1  -- PA0  ���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			     //ʹ�ܰ��� K2  -- PC13  ���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}


//********************************************************************************

//�ⲿ�ж�2�������   �� δ�õ� ��

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			

//********************************************************************************

////
////void EXTI2_IRQHandler(void)
////{
////	delay_ms(10);//����
////	if(KEY2==0)	  //����KEY2
////	{

////	}		 
////	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
////}



//********************************************************************************

//�ⲿ�ж� 3 �������   �� δ�õ� ��

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			

//********************************************************************************


////void EXTI3_IRQHandler(void)
////{
////	delay_ms(10);//����
////	if(KEY1==0)	 //����KEY1
////	{				 

////	}		 
////	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
////}





//********************************************************************************

//�ⲿ�ж�0������� 	  

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			

//********************************************************************************


void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	
	if(KEY_K1==1)	 	 //WK_UP����
	{
		
     K1_Flag=KEY1_PRES;  //���ü�ֵ		
//		 LED_D2_toggle;//��˸LED,��ʾϵͳ��������
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 


//********************************************************************************

//�ⲿ�ж�4������� 	  

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			

//********************************************************************************

void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//����
	
	if(KEY_K2==0)	 //����KEY0
	{
		 K2_Flag=KEY2_PRES;  //���ü�ֵ		
//		LED_D2_toggle;//��˸LED,��ʾϵͳ�������� 
				
	}		
	
	EXTI_ClearITPendingBit(EXTI_Line13);  //���LINE4�ϵ��жϱ�־λ  
	
}
 























/////////////////////////////////�Ա����̣�mcudev.taobao.com///////////////////////////////////////////////////	 

//�ⲿ�ж� ��������	   

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ   

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com			


///////////////////////////////�Ա����̣�devebox.taobao.com		/////////////////////////////////////////////////////   












