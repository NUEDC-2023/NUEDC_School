#include "OLED.h"

int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_cross;

// Internal
void display_Specs(uint8_t Cx, int Cy)
{		
	OLED_ShowBinNum(1,1,Cx,8);
	OLED_ShowSignedNum(2,1,Cy,3);
}

void set_Flags(uint8_t Cx, int Cy){
	if (Cx & 0x07) {
		flag_cross = 1;
		//left
		if (Cx & 0x01) flag_left = 1;
		else flag_left = 0;
		//front
		if (Cx & 0x02) flag_front = 1;
		else flag_front = 0;
		//right
		if (Cx & 0x04) flag_right = 1;
		else flag_right = 0;
	} else {
		flag_cross = 0;
	}
	
	if (Cx & 0x08) flag_trap = 1;
	else flag_trap = 0;
	
	if ((Cx & 0x10) && !flag_trap) flag_treasure = 1;
	else flag_treasure = 0;
}

void OpenMV_On_Recieve(uint8_t Cx, int Cy)
{
	set_Flags(Cx, Cy);
	display_Specs(Cx, Cy);
}
