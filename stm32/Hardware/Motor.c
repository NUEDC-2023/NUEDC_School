#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOD, &GPIO_InitStructure);     
	
	TIM3_PWM_Init(99,359);
}

void Motor_SetSpeed(int8_t Speed)  //摄像头朝向为正方向，right wheel
{
	if (Speed >= 0)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);//PA8=PD12
		GPIO_SetBits(GPIOD, GPIO_Pin_9);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);//PA11 =PD15
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		GPIO_SetBits(GPIOD, GPIO_Pin_9);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		PWM_SetCompare3(-Speed);
	}
}

void Motor_SetSpeed2(int8_t Speed)  //摄像头朝向为正方向，left wheel
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		PWM_SetCompare7(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		PWM_SetCompare7(-Speed);
	}
}
