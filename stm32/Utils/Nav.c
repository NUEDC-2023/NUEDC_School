#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "OpenmvComm.h"
#include "GyroscopeComm.h"
#include "Nav.h"
#include "OLED.h"

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
	if (leftSpeed > 40) leftSpeed = 40;
	if (rightSpeed > 40) rightSpeed = 40;
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


int delay_time = 600;
int foward_speed = 20;
void Detection_Turn_Left(void)
{
	Go_Straight(foward_speed);
	Delay_ms(delay_time);
	Turn_Left();
}

void Detection_Turn_Right(void)
{
	Go_Straight(foward_speed);
	Delay_ms(delay_time);
	Turn_Right();
}

void Turn_Right(void)
{
	Motor_SetSpeed(-20);
	Motor_SetSpeed2(20);
	float start_roll = roll_holder;
	while(1)
	{
		if (start_roll - roll_holder >= 78) 
		{
			break;
		}
	}
	Stop();
}

void Turn_Left(void)
{
	Motor_SetSpeed(20);
	Motor_SetSpeed2(-20);
	float start_roll = roll_holder;
	while(1)
	{
		if (roll_holder - start_roll >= 78) 
		{
			break;
		}
	}
	Stop();
}
void Turn_180(void)
{
	Motor_SetSpeed(-20);
	Motor_SetSpeed2(20);
	float start_roll = roll_holder;
	while(1)
	{
		if (roll_holder - start_roll >= 170) 
		{
			break;
		}
	}
	Stop();
}

int Track_Line(int Speed) {
	//todo:! Stop for a new point when no front line is detected.
	if (flag_turn == 1){
		int temp_left_flag = flag_left, temp_right_flag = flag_right;
		//For better detection.
		Go_Straight(foward_speed);
		Delay_ms(100);
		if (flag_front + flag_left + flag_right >= 2) {
			//for making sure
			Delay_ms(10);
			if (flag_front + flag_left + flag_right >= 2) return 0;  //cross.
			else return 1;
		} else {
			//Car is going straight now.			
			if (temp_left_flag) {
				Detection_Turn_Left();
			} else if (temp_right_flag) {
				Detection_Turn_Right();
			}
		}
	} else {
		line_track(Speed);
	}
	return 1;
}
