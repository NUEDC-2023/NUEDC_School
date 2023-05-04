#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//********************************************************************************

//LED驱动代码	 

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

//LED_D1 --  电源指示灯--供电正亮
//LED_D2 --  PA1	 --低电平点亮   


//********************************************************************************								  
////////////////////////////////////////////////////////////////////////////////// 	   


//LED_D2 --  PA1	初始化


void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能 LED_D2 --  PA1 端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 			 //LED_D2 --  PA1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);									 //根据设定参数初始化PA1

	GPIO_SetBits(GPIOA,GPIO_Pin_1);						             //PA1 输出高-- 状态 --LED灯灭

	
}



































//********************************************************************************

//LED驱动代码	 

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

//********************************************************************************	
 
