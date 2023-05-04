#include "headfile.h"
/************************************************
//STM32F103 开发板  1.8寸液晶屏初始化  SPI 接口  实验

// LED_D2 -- PA1	 --低电平点亮    

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平    

//USART0_TX---PA9     --单片机串口输出
//USART0_RX---PA10    --单片机串口输入

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

************************************************/
//编码器A PA15 PB3
//编码器B PB6 PB7


  uint16_t t;  
	uint16_t len;	
	int time=0;
	
int abs_int(int a)
{
	if(a<0)return -a;
	else return a;
}
 int main(void)
 {	
	 
	delay_init();	    //SysTick 延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级	 

	LED_Init();		  	//初始化与LED连接的硬件接口
	 
	KEY_Init();       //初始化按键 --模式是IO输入模式
  
	//USART1_init(115200);          //串口1     初始化函数 
	 
	LCD_Init();           //初始化LCD 1.8寸液晶屏初始化  SPI 接口 
	RCC_config();
	TIMER_config1();
	TIMER_config2();

	while(1)
	{
		delay_ms(10);
		Read_EncoderA();
		Read_EncoderB();
		//lcd_showint16(64,0,speed1);
		//lcd_showint16(64,1,distance1);
		//lcd_showint16(64,2,speed2);
		//lcd_showint16(64,3,distance2);
		lcd_show();
		time++;
	}
 }



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
/************************************************
	
//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com	

************************************************/

