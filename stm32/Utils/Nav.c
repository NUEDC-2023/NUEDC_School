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
void Go_Straight(void)
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


//Ѳ�ߴ���
void Control(int Speed){
	// Speed not over 100
  float output = pid_cal(Cy,50) +50;
	int leftSpeed = Speed*output/100;
	int rightSpeed = Speed - leftSpeed;
	if (leftSpeed < 20) leftSpeed = 20;
	//if (leftSpeed > 65) leftSpeed = 65;
	if (rightSpeed < 20) rightSpeed = 20;
	//if (rightSpeed > 65) rightSpeed = 65;
	
	//float speed_min;
	//speed_min=output;   //min 30��70ּ�䣬ֻ����ֱ��
  if(output>=0)   //����ת���ҿ죬����
	{
		Motor_SetSpeed(rightSpeed); //���ֵ��
		Motor_SetSpeed2(leftSpeed); //���ֵ��
	}
	else  //��ת �������
	{
		output= -output;
		Motor_SetSpeed(rightSpeed); //���ֵ��
		Motor_SetSpeed2(leftSpeed);  //   ���ֵ��
	}
}



