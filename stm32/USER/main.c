#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Serial.h"
#include "Nav.h"
#include "MoveLogic.h"
#include "OpenmvComm.h"

// Record of global varialble: 
// OpenmvComm: 
// 	 int Cy: For marking the centerline (possible value: 255 | 0 - 100)
//
// 	 uint8_t int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_cross:
//           For marking out the cross (left right front exsitance) / treasure / trap the car is passing()
//

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	uint8_t start_flag = 1; //起始标志位
	//uint8_t element_flag=0; //元素标志位 0正常巡线，1到7 7个多路口  8停止标志位
	
	OLED_Init();  //屏幕初始化
	Motor_Init(); //电机初始化
	KEY_Init();   //按键初始化
	Serial_Gyroscope_Init(); //陀螺仪串口通信初始化
	Serial_Openmv_Init();	//Openmv串口通信初始化
	
	  //以下书写主代码
	while(1)
	{
		
		Gyroscope_Date();
//		if(start_flag == 1)
//		{
//			while(1)
//			{
//				move(60);
//			}
//		}
	}

	
	
//	OLED_ShowString(1, 1, "Speed:");
//	Motor_SetSpeed(60);
//	Motor_SetSpeed2(60);
//	while (1)
//	{
//		if (Serial_GetRxFlag() == 1)
//		{
//			RxData = Serial_GetRxData();
//			Serial_SendByte(RxData);
//			OLED_ShowHexNum(1, 8, RxData, 2);
//		}
//	}
//	while (1)
//	{
//		KeyNum = Key_GetNum();
//		if (KeyNum == 1)
//		{
//			Speed += 20;
//			if (Speed > 100)
//			{
//				Speed = -100;
//			}
//		}
//		Motor_SetSpeed(Speed);
//		OLED_ShowSignedNum(1, 7, Speed, 3);
//	}
//	
}
