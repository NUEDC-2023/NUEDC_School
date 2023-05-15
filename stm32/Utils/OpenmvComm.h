#ifndef __OPENMV_COMM_H
#define __OPENMV_COMM_H

#include <stdint.h>
#include "Serial.h"

extern int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_cross;
extern uint8_t Cx;

void OpenMV_On_Recieve(uint8_t Cx, int Cy);
void OpenMV_Display_Specs();

#endif
