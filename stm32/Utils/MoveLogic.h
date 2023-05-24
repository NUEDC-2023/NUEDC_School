#include "Nav.h"
#include "PID.h" 

#define MAP_UP 4
#define MAP_RIGHT 3
#define MAP_DOWN 2
#define MAP_LEFT 1

#define TURN_RIGHT 1 // -3 when calculating
#define TURN_LEFT -1 //  3 when calculating
#define TURN_BACK 2  // -2 when calc.
#define TURN_AHEAD 0

#define _TURN_RIGHT -3
#define _TURN_LEFT 3
#define _TURN_BACK -2

#define MAP_SIZE 	85
#define MAP_CONTENT_SIZE 3
#define ROUTE_MAP_SIZE 6
#define ROUTE_MAP_CONTENT_SIZE 11

int Correct_Direction(int direction);
int Move_Q1(int speed);
int Move(int Speed);
void Move_Logic_Display(void);
int Simple_Move_Q1(int speed);

extern int Info_Map[MAP_SIZE][MAP_CONTENT_SIZE], cur_direction;
