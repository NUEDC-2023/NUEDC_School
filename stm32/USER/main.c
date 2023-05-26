#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Serial.h"
#include "Nav.h"
#include "MoveLogic.h"
#include "OpenmvComm.h"
#include "Buzzer.h"
#include "Encoder.h"

// Record of global varialble: 
// OpenmvComm: 
// 	 int Cy: For marking the centerline (possible value: 255 | 0 - 100)
//
// 	 uint8_t int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_turn:
//           For marking out the cross (left right front exsitance) / treasure / trap the car is passing()
//

uint8_t KeyNum;
int8_t Speed;
uint8_t start_flag = 0; //��ʼ��־λ
int speed = 32;

int main(void)
{
	//uint8_t element_flag=0; //Ԫ�ر�־λ 0����Ѳ�ߣ�1��7 7����·��  8ֹͣ��־λ
	
	BUZZER_Init();
	//BUZZER_05Sec();
	OLED_Init();  //��Ļ��ʼ��
	Motor_Init(); //�����ʼ��
	KEY_Init(&start_flag);   //������ʼ��
	Serial_Gyroscope_Init(); //�����Ǵ���ͨ�ų�ʼ��
	Encoder_Init();
	Delay_ms(5000); //Omv start up
	Serial_Openmv_Init();	//Openmv����ͨ�ų�ʼ��


	//������д������
	while(1)
	{
		OLED_Show();
		Read_EncoderA();
		if(start_flag == 1)
		{ 
			if (flag_question == 0){
				if(Simple_Move_Q1(speed)) //todo: NEDD a function for changing this on OLED
					break;
			}else if (flag_question == 1){
				if(Move_Q1(speed)) //todo: NEDD a function for changing this on OLED
					break;
			} else if (flag_question == 2) {
				if(Move_Q2(speed)) //todo: NEDD a function for changing this on OLED
					break;
			} else if (flag_question == -1) {
				Motor_SetSpeed(20);
				Motor_SetSpeed2(20);
				Delay_ms(2000);
				Motor_SetSpeed(-20);
				Motor_SetSpeed2(-20);
				Delay_ms(2000);
				Stop();
				start_flag = 0;
			}
		} else {
			Delay_ms(10);
		}
		if (flag_end == 1) {
			Go_Straight(20);
			Encoder_Delay(1700);
			Stop();
			start_flag = 0;
		}
	}
	
	OLED_Clear();
	OLED_ShowString(1, 1, "Prgm ended...");
}
