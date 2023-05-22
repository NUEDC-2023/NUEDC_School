 #include "stm32f10x.h"
 #include "Buzzer.h"
 #include "Delay.h"

 void BUZZER_Init(void){ 
     GPIO_InitTypeDef  GPIO_InitStructure; 
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD ,ENABLE);	 
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                       
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
     GPIO_Init(BUZZERPORT, &GPIO_InitStructure);	
     
     GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); 
 }

 void BUZZER_2Sec(void)
{ //ÏìÁ½Ãëº¯Êý
         GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(0)); 
         Delay_ms(2000); 	
         GPIO_WriteBit(BUZZERPORT,BUZZER,(BitAction)(1)); 
 }
