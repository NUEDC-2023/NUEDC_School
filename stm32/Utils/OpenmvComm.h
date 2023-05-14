#ifndef __OPENMV_COMM_H
#define __OPENMV_COMM_H

#include <stdint.h>
#include "Serial.h"

extern int Cy, flag_treasure, flag_trap, flag_left, flag_right, flag_front, flag_cross;

void OpenMV_On_Recieve(int Cx, int Cy);

#endif
