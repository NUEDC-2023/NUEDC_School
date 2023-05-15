#include "OLED.h"
#include "OpenmvComm.h"

uint8_t Cx;
int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_cross;

// Internal
// 0b00000001(0x01) left 0b00000010(0x02) front    0b00000100(0x04) right
// 0b00001000(0x08) trap 0b00010000(0x10) treasure 0b00000111(0x07) = 0x01|0x02|0x04
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

//Public: 
void OpenMV_Display_Specs()
{		
	OLED_ShowString(1, 1, "OpMv:");
	OLED_ShowBinNum(2,5,Cx,8);
	OLED_ShowSignedNum(3,5,Cy,3);
}

void OpenMV_On_Recieve(uint8_t Cx, int Cy)
{
	set_Flags(Cx, Cy);
}
