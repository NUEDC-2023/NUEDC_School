#ifndef __GYRO_COMM_H
#define __GYRO_COMM_H

#include "OLED.h"
#include "Serial.h"

extern float pitch,roll,yaw;
extern float pitch_holder, yaw_holder, roll_holder;
extern float ring;
extern float T;

void Gyroscope_On_Recieve(void);
void Init_Gyro_Data(void);
void Gyroscope_Display_Specs(void);
	
#endif
