#include "OLED.h"

int flag_treasure,flag_trap,flag_fok;
void OpenMV_On_Recieve(uint8_t Cx, int Cy)
{
	if(Cx==16||Cx==17) flag_treasure=1;
	else flag_treasure=0;
	if(Cx==32||Cx==33) flag_trap=1;
	else flag_trap=0;
	if(Cx%10==1) flag_fok=1;
	else flag_fok=0;
	
	OLED_ShowSignedNum(1,1,flag_treasure,3);
	OLED_ShowSignedNum(2,1,flag_trap,3);
	OLED_ShowSignedNum(3,1,flag_fok,3);
	OLED_ShowSignedNum(4,1,Cy,3);
}