#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "Serial.h"
#include "Nav.h"
#include "OLED.h"
#include "GyroscopeComm.h"

static int search_Move(void){
	
}

int MoveQ1(void)
{
	int move = search_Move();
	//获取目前方位角
	int cur_direction = roll;
	switch(move){
		case 1:
			//向上
			if ()
			break;
		case 2:
			//向下
			break;
		case 3:
			//向左
			break;
		case 4:
			//向右
			break;
	}
}

int Move(int speed) // Temporary movement logic for straight line following
{
	if(!Track_Line(speed)) {
		//routing logic
		Stop(); //Temp turning left
		return 1;
	}
	return 0;
}
