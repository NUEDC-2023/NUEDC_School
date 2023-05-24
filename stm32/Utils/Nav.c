#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "OpenmvComm.h"
#include "GyroscopeComm.h"
#include "Nav.h"
#include "OLED.h"
#include "MoveLogic.h"
#include "Encoder.h"

// int delay_time = 700;
int foward_speed = 25;
int turn_speed = 18;
int turn_angle = 75;
int enc_delay = 755;
int mark = 620;
long long int ideal_heading = 0;
int angle_diff = 0;
//Internal:
//巡线代码
static void line_track(int Speed){
	if (Cy == 256) //256 for no detection.
	{
		//Slowly go ahead when no black line is detected.
		Motor_SetSpeed(Speed*0.6);
		Motor_SetSpeed2(Speed*0.6);
		Delay_ms(50);
		return;
	} // Easier for later calc.
	
	angle_diff = roll_holder - ideal_heading;
  Cy += angle_diff;
	//todo: debug only
	
  float output = pid_cal(Cy,50) +50;
	int leftSpeed = Speed*output/100;
	int rightSpeed = Speed - leftSpeed;
	if (leftSpeed > 40) leftSpeed = 40;
	if (rightSpeed > 40) rightSpeed = 40;
	if (leftSpeed < 15) leftSpeed = 15;
	if (rightSpeed < 15) rightSpeed = 15;
	
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
	Motor_SetSpeed2(speed*0.9);
}

void Detection_Turn_Left(void)
{
	OLED_Clear();
	OLED_ShowString(1, 1, "Detection_Turn_Left...");
  Go_Straight(foward_speed);
	Encoder_Delay(enc_delay);
	Turn_Left();
	Stop();
	Delay_ms(50);
}

void Detection_Turn_Right(void)
{
	OLED_Clear();
	OLED_ShowString(1, 1, "Detection_Turn_Right...");
  Go_Straight(foward_speed);
	Encoder_Delay(enc_delay);
	Turn_Right();
	Stop();
	Delay_ms(50);
}

void Turn_Right(void)
{
	Motor_SetSpeed(-turn_speed);
	Motor_SetSpeed2(turn_speed);
	while(1)
	{
		if (ideal_heading - roll_holder >= turn_angle) 
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
	Motor_SetSpeed(turn_speed);
	Motor_SetSpeed2(-turn_speed);
	while(1)
	{
		if (roll_holder - ideal_heading >= turn_angle) 
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
	cur_direction = cur_direction -2; //todo: Robustness decreased, as the direction is dedicated by turning rather than real heading.
	cur_direction = Correct_Direction(cur_direction);
}

int Track_Line(int Speed) {
	//todo:! Stop for a new point when no front line is detected.
	sent_data1(flag_left,flag_right,flag_front,flag_turn,Cy,0);
	if (flag_turn == 1){
		int temp_left_flag = flag_left, temp_right_flag = flag_right;
		Delay_ms(15);
		if (flag_bug_sentinal){
			flag_bug_sentinal = 0;
			return 0;
		}
		if (flag_front + flag_left + flag_right >= 2 ) {
			return 0;
		} else {		
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

int Simple_Track_Line(int Speed) {
	if (flag_turn == 1){
		return 1;
	} else if (flag_end == 1) {
		return 2;
	} else{
		line_track(Speed);
	}
	return 0;
}
