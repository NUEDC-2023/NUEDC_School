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

// Record of global varialble: 
// OpenmvComm: 
// 	 int Cy: For marking the centerline (possible value: 255 | 0 - 100)
//
// 	 uint8_t int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_turn:
//           For marking out the cross (left right front exsitance) / treasure / trap the car is passing()
//

uint8_t KeyNum;
int8_t Speed;
uint8_t start_flag = 1; //��ʼ��־λ

int main(void)
{
	//uint8_t element_flag=0; //Ԫ�ر�־λ 0����Ѳ�ߣ�1��7 7����·��  8ֹͣ��־λ
	
	Delay_ms(5000); //Omv start up
	OLED_Init();  //��Ļ��ʼ��
	Motor_Init(); //�����ʼ��
	KEY_Init();   //������ʼ��
	Serial_Gyroscope_Init(); //�����Ǵ���ͨ�ų�ʼ��
	Serial_Openmv_Init();	//Openmv����ͨ�ų�ʼ��
	BUZZER_Init();
	
	//������д������
	while(1)
	{
		OLED_Show();
		if(start_flag == 1)
		{ 
//			Motor_SetSpeed(30);
//			Motor_SetSpeed2(30);
			if(Move_Q1(30)) //CHANGE PID IF CHANGE THIS //todo!: NEDD a function for changing this on OLED
				break;
		}
	}

	OLED_Clear();
	OLED_ShowString(1, 1, "Prgm ended...");
}
