#include "headfile.h"
/************************************************
//STM32F103 ������  1.8��Һ������ʼ��  SPI �ӿ�  ʵ��

// LED_D2 -- PA1	 --�͵�ƽ����    

// K1  -- PA0        K1   ���� --���º󣬸ߵ�ƽ  
// K2  -- PC13       K2   ���� --���º󣬵͵�ƽ    

//USART0_TX---PA9     --��Ƭ���������
//USART0_RX---PA10    --��Ƭ����������

//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com	

************************************************/
//������A PA15 PB3
//������B PB6 PB7


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
	 
	delay_init();	    //SysTick ��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	 

	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	 
	KEY_Init();       //��ʼ������ --ģʽ��IO����ģʽ
  
	//USART1_init(115200);          //����1     ��ʼ������ 
	 
	LCD_Init();           //��ʼ��LCD 1.8��Һ������ʼ��  SPI �ӿ� 
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
	
//STM32F103����ģ��-�⺯���汾
//DevEBox  ��Խ����

//�Ա����̣�mcudev.taobao.com
//�Ա����̣�devebox.taobao.com	

************************************************/

