#include "stdio.h"	
#include "stm32f10x.h"                  // Device header
#define ENCODER_TIM_PERIOD 0
extern 	int speed1,speed2,distance1,distance2;

void Read_EncoderB(void);
void Read_EncoderA(void);
void TIMER_config2(void);
void Encoder_Init(void);
void TIMER_config1(void);
void Encoder_Display_Content(void);
void Encoder_Delay(int marks);
