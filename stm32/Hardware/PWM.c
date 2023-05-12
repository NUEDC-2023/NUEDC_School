#include "stm32f10x.h"                  // Device header

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//?????3??
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);  //??GPIO???AFIO????????

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer3?????  TIM3_CH2->PB5    
   //????????????,??TIM3 CH2?PWM????	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //??????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//???GPIO
 
   //???TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //???????????????????????????
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //??????TIMx??????????? 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //??TIM_TimeBaseInitStruct?????????TIMx???????
	
	//???TIM3 Channel2 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //??T??????????TIM3 OC2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //??T??????????TIM3 OC2

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //??TIM3?CCR2????????
 	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //??TIM3?CCR2????????

	TIM_Cmd(TIM3, ENABLE);  //??TIM3
	
}
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, 100-Compare);
}

void PWM_SetCompare7(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, 100-Compare);
}