#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"


//////////////////////////////////////////////////////////////////////////////////	 

//外部中断 驱动代码	   

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			


//////////////////////////////////////////////////////////////////////////////////   


//********************************************************************************

// 初始化外部中断 

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			

//********************************************************************************
void EXTIX_Init(void)
{
 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

   //PE.2 中断线以及中断初始化配置   下降沿触发
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

////  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
////  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
////  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

////   //PE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
////  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
////	
////  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
////	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
////  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //K2  -- PC13   中断线以及中断初始化配置  下降沿触发	//K2   按键 --按下后，低电平   
	 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
		
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发中断
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   //K1  -- PA0        K1 中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;                  //K1  -- PA0 
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    //上升沿触发中断
  	EXTI_Init(&EXTI_InitStructure);														//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键  K1  -- PA0  所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			     //使能按键 K2  -- PC13  所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}


//********************************************************************************

//外部中断2服务程序   （ 未用到 ）

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			

//********************************************************************************

////
////void EXTI2_IRQHandler(void)
////{
////	delay_ms(10);//消抖
////	if(KEY2==0)	  //按键KEY2
////	{

////	}		 
////	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
////}



//********************************************************************************

//外部中断 3 服务程序   （ 未用到 ）

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			

//********************************************************************************


////void EXTI3_IRQHandler(void)
////{
////	delay_ms(10);//消抖
////	if(KEY1==0)	 //按键KEY1
////	{				 

////	}		 
////	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
////}





//********************************************************************************

//外部中断0服务程序 	  

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			

//********************************************************************************


void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	
	if(KEY_K1==1)	 	 //WK_UP按键
	{
		
     K1_Flag=KEY1_PRES;  //设置键值		
//		 LED_D2_toggle;//闪烁LED,提示系统正在运行
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}
 


//********************************************************************************

//外部中断4服务程序 	  

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			

//********************************************************************************

void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//消抖
	
	if(KEY_K2==0)	 //按键KEY0
	{
		 K2_Flag=KEY2_PRES;  //设置键值		
//		LED_D2_toggle;//闪烁LED,提示系统正在运行 
				
	}		
	
	EXTI_ClearITPendingBit(EXTI_Line13);  //清除LINE4上的中断标志位  
	
}
 























/////////////////////////////////淘宝店铺：mcudev.taobao.com///////////////////////////////////////////////////	 

//外部中断 驱动代码	   

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平   

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			


///////////////////////////////淘宝店铺：devebox.taobao.com		/////////////////////////////////////////////////////   












