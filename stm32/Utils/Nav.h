#include "stm32f10x.h"                  // Device header

void Stop(void);
void Go_Straight(int speed);
void Turn_Left(void);
void Turn_Right(void);
void Detection_Turn_Left(void);
void Detection_Turn_Right(void);
void Turn_180(void);
int Track_Line(int Fix_Speed);
