#ifndef __BUZZER_H
#define __BUZZER_H	 
#define BUZZERPORT	GPIOB	//??IO??
#define BUZZER	GPIO_Pin_5	//??IO??

void BUZZER_Init(void);
void BUZZER_2Sec(void);
void MIDI_PLAY(void);                    
#endif
