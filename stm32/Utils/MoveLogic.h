#include "Nav.h"
#include "PID.h" 

#define MAP_UP 1
#define MAP_RIGHT 2
#define MAP_DOWN 3
#define MAP_LEFT 4

#define TURN_RIGHT 1 // -3 when calculating
#define TURN_LEFT -1 //  3 when calculating
#define TURN_BACK 2  // -2 when calc.
#define TURN_AHEAD 0

#define _TURN_RIGHT -3
#define _TURN_LEFT 3
#define _TURN_BACK -2

#define MAP_SIZE 	7
#define MAP_CONTENT_SIZE 3

int Move_Q1(int speed);
int Move(int Speed);

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