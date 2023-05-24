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
uint8_t start_flag = 1; //起始标志位

int main(void)
{
	//uint8_t element_flag=0; //元素标志位 0正常巡线，1到7 7个多路口  8停止标志位
	
	BUZZER_Init();
	//BUZZER_05Sec();
	OLED_Init();  //屏幕初始化
	Motor_Init(); //电机初始化
	KEY_Init();   //按键初始化
	Serial_Gyroscope_Init(); //陀螺仪串口通信初始化
	Encoder_Init();
	Delay_ms(5000); //Omv start up
	Serial_Openmv_Init();	//Openmv串口通信初始化
	
	//以下书写主代码
	while(1)
	{
		OLED_Show();
		Read_EncoderA();
		sent_data1(flag_left,flag_right,flag_front,flag_turn,flag_end,Cx);
		if(start_flag == 1)
		{ 
//			Motor_SetSpeed2(20);
//			Motor_SetSpeed(20);
			if(Simple_Move_Q1(25)) //CHANGE PID IF CHANGE THIS //todo!: NEDD a function for changing this on OLED
				break;
		}
	}

	OLED_Clear();
	OLED_ShowString(1, 1, "Prgm ended...");
}
