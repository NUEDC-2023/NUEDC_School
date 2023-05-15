#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "Serial.h"
#include "Nav.h"
#include "OLED.h"

//void move (int element_flag)     //要求摄像头检测到不同多路口时返回不同的值，并及时清零
// {
//	 int Fix_Speed = 50; //Totial speed
//   switch(element_flag)
//   {      
//      case 0:                          //基本巡线
//      {
//            Control(Fix_Speed, );
//      }
//      case 3:                            //多路口处理：直走
//      {
//              Straight();
//      }
//      case 2:                           //多路口处理：右转
//      case 5:
//      case 7:
//      {
//                Turn_Right();
//      }
//      case 1:                           //多路口处理：左转
//      case 4:
//      case 6:
//      {
//        Turn_Left();
//      }
//      case 8:                           //检测到蓝色时调用 ：停止
//      {
//         Straight();
//		  	 Delay_ms(200);//需调，让车尾在蓝色区域
//			   Stop();
//      }
//   }
//}

int Move(int speed) // Temporary movement logic for straight line following
{
	if(!Track_Line(speed)) {
		//routing logic
		Stop(); //Temp turning left
		return 1;
	}
	return 0;
}
