#include "MoveLogic.h"
#include "Motor.h"
#include "Delay.h"
#include "PID.h"
#include "Serial.h"
#include "Nav.h"
#include "OLED.h"
#include "GyroscopeComm.h"
#include "Buzzer.h"
#include "Encoder.h"
#include "OpenmvComm.h"

int flag_bug_sentinal = 0;
int cur_direction = MAP_LEFT;
int flag_area = 2;
int flag_treasure_found = 0;
int Info_Map[MAP_SIZE][MAP_CONTENT_SIZE] = 
{
	{1, 2, MAP_DOWN},
	{1, 40, MAP_LEFT},
	{2, 1, MAP_UP},
	{2, 3, MAP_LEFT},
	{2, 21, MAP_RIGHT},
	{3, 2, MAP_RIGHT},
	{3, 35, MAP_DOWN},
	{3, 4, MAP_LEFT},
	{4, 5, MAP_DOWN},
	{4, 16, MAP_UP},
	{5, 4, MAP_UP},
	{5, 6, MAP_LEFT},
	{6, 5, MAP_RIGHT},
	{6, 7, MAP_DOWN},
	{6, 18, MAP_LEFT},
	{7, 6, MAP_UP},
	{7, 8, MAP_LEFT},
	{7, 32, MAP_RIGHT},
	{9, 11, MAP_LEFT},
	{9, 10, MAP_UP},
	{9, 40, MAP_RIGHT},
	{10, 9, MAP_UP},
	{11, 9, MAP_RIGHT},
	{11, 12, MAP_UP},
	{11, 40, MAP_DOWN},
	{12, 11, MAP_RIGHT},
	{12, 13, MAP_LEFT},
	{12, 15, MAP_DOWN},
	{13, 34, MAP_DOWN},
	{13, 14, MAP_LEFT},
	{13, 12, MAP_RIGHT},
	{14, 13, MAP_UP},
	{15, 12, MAP_UP},
	{15, 16, MAP_RIGHT},
	{15, 18, MAP_LEFT},
	{15, 17, MAP_DOWN},
	{16, 15, MAP_UP},
	{16, 20, MAP_RIGHT},
	{16, 4, MAP_DOWN},
	{17, 15, MAP_RIGHT},
	{18, 15, MAP_UP},
	{18, 19, MAP_DOWN},
	{18, 6, MAP_RIGHT},
	{19, 18, MAP_UP},
	{20, 16, MAP_LEFT},
	{21, 2, MAP_LEFT},
	{21, 22, MAP_UP},
	{21, 24, MAP_DOWN},
	{22, 21, MAP_DOWN},
	{23, 24, MAP_LEFT},
	{24, 23, MAP_UP},
	{24, 36, MAP_LEFT},
	{24, 21, MAP_RIGHT},
	{24, 25, MAP_DOWN},
	{25, 24, MAP_UP},
	{25, 30, MAP_LEFT},
	{25, 26, MAP_RIGHT},
	{26, 25, MAP_LEFT},
	{26, 27, MAP_UP},
	{26, 29, MAP_RIGHT},
	{27, 26, MAP_DOWN},
	{28, 29, MAP_DOWN},
	{29, 26, MAP_LEFT},
	{29, 28, MAP_UP},
	{30, 25, MAP_DOWN},
	{30, 31, MAP_LEFT},
	{30, 32, MAP_UP},
	{31, 30, MAP_RIGHT},
	{31, 32, MAP_LEFT},
	{31, 33, MAP_DOWN},
	{32, 7, MAP_UP},
	{32, 30, MAP_RIGHT},
	{32, 31, MAP_DOWN},
	{33, 31, MAP_DOWN},
	{34, 13, MAP_UP},
	{35, 5, MAP_LEFT},
	{35, 3, MAP_UP},
	{35, 36, MAP_DOWN},
	{36, 35, MAP_UP},
	{36, 37, MAP_LEFT},
	{36, 24, MAP_DOWN},
	{37, 36, MAP_RIGHT},
	{40, 9, MAP_UP},
	{40, 11, MAP_LEFT},
	{40, 1, MAP_DOWN},
};



//-1 for end.
int route_Map[ROUTE_MAP_SIZE][ROUTE_MAP_CONTENT_SIZE] = 
{
	{0},
	{2, 21, 22, 21, 24, 25, 26, 27, 26, 29, 28},
}; 
static int is_End_Point(int current_point){
	for (int i = 0; i < MAP_SIZE; i++) {
		if (Info_Map[i][0] == current_point){
			if (Info_Map[i +1][0] == current_point){
				return 0;
			}
			return 1;
		}	
	}
}
static int search_Q1_Next_Point(int current_point)
{
	if (current_point == 1)
		flag_bug_sentinal = 1;
	return current_point +1;
}

static int search_Q2_Next_Point(int current_point)
{
	if (current_point == 1)
		flag_bug_sentinal = 1;
	int* route = route_Map[flag_area-1];
	
	//Haven't get on the branch
	if (current_point < 8 && !flag_treasure_found){
		if (current_point == route[0]) {
			return route[1];
		} else {
			return search_Q1_Next_Point(current_point);
		}
	}
	
	//on the branch, not found
	if (current_point > 8 && !flag_treasure_found)
	{
		int index = 0;
		for (; index < ROUTE_MAP_CONTENT_SIZE; index++) {
			if(route[index] == current_point){
				return route[index +1];
			}
		} 
	}
	
	if (current_point > 8 && flag_treasure_found){
		//going back
		int index = 0;
		for (; index < ROUTE_MAP_CONTENT_SIZE; index++) {
			if(route[index] == current_point){
				if (is_End_Point(route[index - 1])){
					return route[index - 3];
				}
				return route[index -1];
			}
		} 
	}
	
	//found
	if (current_point < 8 && flag_treasure_found){
		return search_Q1_Next_Point(current_point);
	}
	
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
	int direction = cur_direction - next_direction ;
	direction = Correct_Direction(direction);
	//delete this, debug only:
	Stop();
	BUZZER_05Sec();
	Delay_ms(500);	
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

int cur_point = 1;
int Simple_Move_Q1(int speed)
{
	//todo!: lack return 0 condition detection.
	static int itr = 0;
	int map[] = {TURN_LEFT, TURN_LEFT, TURN_RIGHT, TURN_RIGHT, TURN_LEFT, TURN_RIGHT, TURN_LEFT, TURN_RIGHT, TURN_AHEAD, TURN_LEFT, TURN_RIGHT, TURN_LEFT, TURN_RIGHT, TURN_LEFT, TURN_RIGHT, TURN_LEFT, TURN_LEFT, TURN_RIGHT, TURN_RIGHT};
	int out = Simple_Track_Line(speed);
	if(out == 1) 
	{
		switch(map[itr])
		{
			case TURN_RIGHT:
				Detection_Turn_Right();
				break;
			case TURN_LEFT:
				Detection_Turn_Left();
				break;
			case TURN_BACK:
				Turn_180();
				break;
			case TURN_AHEAD:
				OLED_Clear();
				OLED_ShowString(1, 1, "TURN_AHEAD...");
				Go_Straight(20);
				Delay_ms(300);
				break;
		}
		itr++;
	} 
	return 0;
}
int Move_Q1(int speed)
{
	if(!Track_Line(speed)) {
		//routing logic		
		int next_point = search_Q1_Next_Point(cur_point);
		int turn = get_Turn_Direction(cur_point, next_point);
		switch(turn)
		{
			case TURN_RIGHT:
				Detection_Turn_Right();
				Stop();
			  Delay_ms(300);
				break;
			case TURN_LEFT:
				Detection_Turn_Left();
				Stop();
			  Delay_ms(300);
				break;
			case TURN_BACK:
				Turn_180();
				break;
			case TURN_AHEAD:
				OLED_Clear();
				OLED_ShowString(1, 1, "TURN_AHEAD...");
				Go_Straight(22);
				Encoder_Delay(300);
				break;
		}
		cur_point = next_point;
	}
	return 0;
}
int Move_Q2(int speed)
{
	if(!Track_Line(speed))
	{
		
		//routing logic		
		int next_point = search_Q2_Next_Point(cur_point);
		int turn = get_Turn_Direction(cur_point, next_point);
		switch(turn)
		{
			case TURN_RIGHT:
				Detection_Turn_Right();
				break;
			case TURN_LEFT:
				Detection_Turn_Left();
				break;
			case TURN_BACK:
				Turn_180();
				break;
			case TURN_AHEAD:
				OLED_Clear();
				OLED_ShowString(1, 1, "TURN_AHEAD...");
				Go_Straight(20);
				Delay_ms(300);
				break;
		}
		cur_point = next_point;
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
