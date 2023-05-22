#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "OpenmvComm.h"
#include "GyroscopeComm.h"
#include "Nav.h"
#include "OLED.h"
#include "MoveLogic.h"

int delay_time = 700;
int foward_speed = 23;
long long int ideal_heading = 0;
//Internal:
//巡线代码
static void line_track(int Speed){
	// Easier to grab when visual rec is out of control.
	if (Cy == 256) //256 for stopping
	{
		//Slowly go ahead when no black line is detected.
		Motor_SetSpeed(Speed/1.4);
		Motor_SetSpeed2(Speed/1.6);
		Delay_ms(50);
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

void Detection_Turn_Left(void)
{
	OLED_Clear();
	OLED_ShowString(1, 1, "Detection_Turn_Left...");
	Go_Straight(foward_speed);
	Delay_ms(delay_time);
	Turn_Left();
}

void Detection_Turn_Right(void)
{
	OLED_Clear();
	OLED_ShowString(1, 1, "Detection_Turn_Right...");
	Go_Straight(foward_speed);
	Delay_ms(delay_time);
	Turn_Right();
}

void Turn_Right(void)
{
	Motor_SetSpeed(-20);
	Motor_SetSpeed2(20);
	while(1)
	{
		if (ideal_heading - roll_holder >= 80) 
		{
			break;
		}
	}
	Stop();
	ideal_heading -= 90; 
	cur_direction = cur_direction -1;
	cur_direction = Correct_Direction(cur_direction);
}

void Turn_Left(void)
{
	Motor_SetSpeed(20);
	Motor_SetSpeed2(-20);
	while(1)
	{
		if (roll_holder - ideal_heading >= 80) 
		{ 
			break;
		} 
	}
	Stop();
	ideal_heading += 90; 
	cur_direction = cur_direction +1; //todo: Robustness decreased, as the direction is ddicated by turning rather than real heading.
	cur_direction = Correct_Direction(cur_direction);
}
void Turn_180(void)
{
	Motor_SetSpeed(-20);
	Motor_SetSpeed2(20);
	while(1)
	{
		if (roll_holder - ideal_heading <= - 170) 
		{
			break;
		}
	}
	Stop();
	ideal_heading -= 180; 
	cur_direction = cur_direction -2; //todo: Robustness decreased, as the direction is ddicated by turning rather than real heading.
	cur_direction = Correct_Direction(cur_direction);
}

int Track_Line(int Speed) {
	//todo:! Stop for a new point when no front line is detected.
	if (flag_turn == 1){
		int temp_left_flag = flag_left, temp_right_flag = flag_right;
		if (flag_front + flag_left + flag_right >= 2) {
			//for making sure
			Delay_ms(10);
			if (flag_front + flag_left + flag_right >= 2) {
				//Delete this, debug only
//				Stop();
//				OLED_Clear();
//				OLED_ShowString(1, 1, "Turn detected..");
//				OLED_ShowNum(2, 1, flag_left, 1);
//				OLED_ShowNum(2, 3, flag_front, 1);
//				OLED_ShowNum(2, 5, flag_right, 1);
//				Delay_ms(5000);
				return 0;
			} else return 1;
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
