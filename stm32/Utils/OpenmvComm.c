#include "OLED.h"

int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_cross;

// Internal
void display_Specs(uint8_t Cx, int Cy)
{		
	if (Cx&0b00000111) {
		flag_cross = 1;
		//left
		if (Cx&0b00000001) flag_left = 1;
		else flag_left = 0;
		//front
		if (Cx&0b00000010) flag_left = 1;
		else flag_front = 0;
		//right
		if (Cx&0b00000100) flag_left = 1;
		else flag_right = 0;
	} else {
		flag_cross = 0;
	}
	
	if (Cx&0b00001000) flag_trap = 1;
	else flag_trap = 0;
	
	if (Cx&0b00010000 && !flag_trap) flag_treasure = 1;
	else flag_treasure = 0;
	
	OLED_ShowBinNum(1,1,Cx,8);
	OLED_ShowSignedNum(2,1,Cy,3);
}

void OpenMV_On_Recieve(uint8_t Cx, int Cy)
{
	display_Specs(Cx, Cy);
}
