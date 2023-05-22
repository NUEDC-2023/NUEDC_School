 #include "stm32f10x.h"
 #include "Buzzer.h"
 #include "Delay.h"

void BUZZER_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //??PA????
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //BEEP--PA5????
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //?????????GPIOA.5
	GPIO_SetBits(GPIOD,GPIO_Pin_10);
}

void BUZZER_2Sec(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);		
  Delay_ms(2000);	
	GPIO_SetBits(GPIOD,GPIO_Pin_10);	
}
