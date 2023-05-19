#include "MoveLogic.h"
#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "Serial.h"
#include "Nav.h"
#include "OLED.h"
#include "GyroscopeComm.h"

int cur_direction = MAP_LEFT;
int Info_Map[MAP_SIZE][MAP_CONTENT_SIZE] = 
{
	{1, 2, MAP_DOWN},
	{2, 3, MAP_LEFT},
	{3, 4, MAP_LEFT},
	{4, 5, MAP_DOWN},
	{5, 6, MAP_LEFT},
	{6, 7, MAP_DOWN},
	{7, 8, MAP_LEFT}
};

static int search_Q1_Next_Point(int current_point)
{
	return current_point +1;
}

static int get_Turn_Direction(int cur_point, int next_point)
{
	int next_direction;
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

	//calc. turning direction:
	int direction = next_direction - cur_direction ;
	direction = Correct_Direction(direction);
	return direction;
}

int Correct_Direction(int direction)
{
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
			int next_point = search_Q1_Next_Point(cur_point);
			int turn = get_Turn_Direction(cur_point, next_point);
			Stop();
			OLED_Clear();
			OLED_ShowString(1, 1, "Point!!!(Cur)");
			OLED_ShowNum(2, 1, cur_point, 2);	OLED_ShowString(2, 3, "->");OLED_ShowNum(2, 7, next_point, 3);	
			OLED_ShowSignedNum(3, 1, turn, 3);
			Delay_ms(3000); //todo: change this back for relaease.
			switch(turn)
			{
				case TURN_RIGHT:
					Detection_Turn_Right();
				case TURN_LEFT:
					Detection_Turn_Left();
				case TURN_BACK:
					Turn_180();
				case TURN_AHEAD:
					OLED_Clear();
					OLED_ShowString(1, 1, "TURN_AHEAD...");
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
void Move_Logic_Display()
{
	OLED_Clear();
	OLED_ShowString(1, 1, "Cur Direction: ");
	OLED_ShowSignedNum(2, 3, cur_direction, 3);
}
