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

//Ѳ�ߴ���
void Control(int Fix_Speed, int Cy){
  float output = pid_cal(Cy,50);
	float speed_min;
  if(output>=0)   //��ת����Ҫ�����������ֿ�
	{
		speed_min=30/(output+1);
		Motor_SetSpeed(speed_min); //���ֵ��
		Motor_SetSpeed2(Fix_Speed); //���ֵ��
	}
	else  //��ת����Ҫ���ֿ죬������
		{
		speed_min=30/(-output+1);	
		Motor_SetSpeed(Fix_Speed); //���ֵ��
		Motor_SetSpeed2(speed_min);  //   ���ֵ��
	}
}


