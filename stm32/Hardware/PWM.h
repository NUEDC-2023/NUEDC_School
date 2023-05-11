#ifndef __PWM_H
#define __PWM_H


void TIM3_PWM_Init(u16 arr,u16 psc);

void PWM_SetCompare3(uint16_t Compare);
void PWM_SetCompare7(uint16_t Compare);
#endif
