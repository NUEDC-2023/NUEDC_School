#include "MoveLogic.h"
#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "Serial.h"
#include "Nav.h"
#include "OLED.h"
#include "GyroscopeComm.h"

static int search_Q1_Next_Point(int current_point)
{
	return current_point +1;
}

static int get_Turn_Direction(int cur_point, int next_point)
{
	int next_direction, cur_direction;
	//search through the map
	for(int i = 0; i < MAP_SIZE; i++)
	{
		if (Info_Map[i][0] != cur_point) 
		{
			continue;
		}
		if (Info_Map[i][1] != next_point) 
		{
			continue;
		}
		next_direction = Info_Map[i][2];
		break;
	}
	
	//get cur direction.
	//todo:! How does this work, which indecates which?
	if (roll > 0){}
	
	//calc. turning direction:
	int direction = cur_direction - next_direction;
	switch(direction)
	{
		case _TURN_LEFT:
			return TURN_LEFT;
		case _TURN_RIGHT:
			return TURN_RIGHT;
		case _TURN_BACK:
			return TURN_BACK;
		default:
			return direction;
	}
	
	return 0;
}

int Move_Q1(int speed)
{
	int cur_point = 0;
	if(!Track_Line(speed)) {
		//routing logic
		if (cur_point == 8) //todo:! Change this, this is not the right way to detect the end point.
		{
			Stop();
			return 1;
		}
		else 
		{
			Stop();
			Delay_ms(200);
			int next_point = search_Q1_Next_Point(cur_point);
			int turn = get_Turn_Direction(cur_point, next_point);
			switch(turn)
			{
				case TURN_RIGHT:
					Detection_Turn_Right();
				case TURN_LEFT:
					Detection_Turn_Left();
				case TURN_BACK:
					Turn_180();
				case TURN_AHEAD:
					Go_Straight(20);
					Delay_ms(500);
			}
			cur_point = next_point;
		}
	}
	return 0;
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
