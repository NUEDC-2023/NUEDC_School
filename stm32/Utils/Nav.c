#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "Serial.h"
void Stop(void)
{	
  Motor_SetSpeed(0);
	Motor_SetSpeed2(0);
}

// Turning control
void Straight(void)
{
	Motor_SetSpeed(20);
	Motor_SetSpeed2(20);
}

void Turn_Right(void)
{
	Motor_SetSpeed(20);
	Motor_SetSpeed2(-20);
	Delay_ms(1000);
	Stop();
}

void Turn_Left(void)
{
	Motor_SetSpeed(-20);
	Motor_SetSpeed2(20);
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

//巡线代码
void Control(int Fix_Speed, int Cy){
  float output = pid_cal(Cy,50);
	float speed_min;
  if(output>=0)   //右转，需要右轮慢，左轮快
	{
		speed_min=30/(output+1);
		Motor_SetSpeed(speed_min); //右轮电机
		Motor_SetSpeed2(Fix_Speed); //左轮电机
	}
	else  //左转，需要右轮快，左轮慢
		{
		speed_min=30/(-output+1);	
		Motor_SetSpeed(Fix_Speed); //右轮电机
		Motor_SetSpeed2(speed_min);  //   左轮电机
	}
}


