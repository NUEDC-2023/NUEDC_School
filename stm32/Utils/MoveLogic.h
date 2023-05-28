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
#define ROUTE_MAP_SIZE 8
#define ROUTE_MAP_CONTENT_SIZE 11

extern int flag_bug_sentinal;
extern int flag_question;

int Correct_Turn(int turn);
int Move_Q1(int speed);
int Move_Q2(int speed);
int Simple_Move_Q1(int speed);
int Move(int Speed);
void Move_Logic_Display(int is_start);
void Change_Mode(int change_by);
void Change_Route(int change_by);

extern int Info_Map[MAP_SIZE][MAP_CONTENT_SIZE], cur_direction, flag_treasure_found, cur_point;
