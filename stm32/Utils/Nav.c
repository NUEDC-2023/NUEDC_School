#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "OpenmvComm.h"
#include "Nav.h"

//Internal:
//巡线代码
void line_track(int Speed){
	// Easier to grab when visual rec is out of control.
	if (Cy == 255) 
	{
		//Slowly go ahead when no black line is detected.
		Motor_SetSpeed(20);
		Motor_SetSpeed2(20);
		return;
	} // Easier for later calc.
	
  float output = pid_cal(Cy,50) +50;
	int leftSpeed = Speed*output/100;
	int rightSpeed = Speed - leftSpeed;
	if (leftSpeed < 20) leftSpeed = 20;
	if (rightSpeed < 20) rightSpeed = 20;
	
  if(output>=0)   //向左转，右快，左慢
	{
		Motor_SetSpeed(rightSpeed); //右轮电机
		Motor_SetSpeed2(leftSpeed); //左轮电机
	}
	else  //右转 右慢左快
	{
		output= -output;
		Motor_SetSpeed(rightSpeed); //右轮电机
		Motor_SetSpeed2(leftSpeed);  //   左轮电机
	}
}

//Public: 
void Stop(void)
{	
  Motor_SetSpeed(0);
	Motor_SetSpeed2(0);
}

// Turning control
void Go_Straight(int speed)
{
	Motor_SetSpeed(speed);
	Motor_SetSpeed2(speed);
}

void Turn_Right(void)
{
	Motor_SetSpeed(40);
	Motor_SetSpeed2(0);
	Delay_ms(1000);
	Stop();
}

void Turn_Left(void)
{
	Motor_SetSpeed(0);
	Motor_SetSpeed2(40);
	Delay_ms(1000);
	Stop();
}
void Turn_180(void)
{
	Motor_SetSpeed(-20);
	Motor_SetSpeed2(20);
	Delay_ms(2000);
	Stop();
}

int Track_Line(int Speed) {
	int detection_time = 20;
	int delay_time = 100;
	int foward_speed = 40;
	//Include dealing with corners
	if (flag_turn == 1){
		Go_Straight(foward_speed);
		Delay_ms(detection_time); //todo: Time tuning needed, for deciding the cross/turn properly.
		
		
		Go_Straight(foward_speed);
		Delay_ms(delay_time);
		if (flag_front + flag_left + flag_right != 1) {
			//cross.
			return 0;
		} else {
			//Car is going straight now.			
			if (flag_left) {
				Turn_Left();
			} else if (flag_right) {
				Turn_Right();
			}
		}
	} else {
		line_track(Speed);
	}
}





