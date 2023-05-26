#ifndef __KEY_H
#define __KEY_H	 


extern int time;


#define lcd_showint16(a,b,c) OLED_ShowSignedNum(b+1,(a/16)+4,c,5)
#define lcd_showstr(a,b,c,d) OLED_ShowString(b,a/16,d)
#define ls1(a) 		lcd_showint16(80,1,a)
#define ls2(a) 		lcd_showint16(80,2,a)
#define ls3(a) 		lcd_showint16(80,3,a)
#define ls4(a) 		lcd_showint16(80,4,a)


#define yf2h1_nc  lcd_showstr(16, 1, 6,"1");ls1(time);
#define yf2h2_nc  lcd_showstr(16, 2, 6,"2");ls2(time);
#define yf2h3_nc  lcd_showstr(16, 3, 6, "3");ls3(time);
#define yf2h4_nc  lcd_showstr(16, 4, 6, "4");ls4(time);

#define yf2h1_c  ls1(time);
#define yf2h2_c  ls2(time);
#define yf2h3_c  ls3(time);
#define yf2h4_c  ls4(time);

#define opr_yf2h1_add
#define opr_yf2h2_add
#define opr_yf2h3_add
#define opr_yf2h4_add

#define opr_yf2h1_cut
#define opr_yf2h2_cut
#define opr_yf2h3_cut
#define opr_yf2h4_cut


#define yf1h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define yf1h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define yf1h3_nc  lcd_showstr(16, 3, 6, "right");ls3(time);
#define yf1h4_nc  lcd_showstr(16, 4, 6, "right");ls4(time);

#define yf1h1_c  ls1(time);
#define yf1h2_c 
#define yf1h3_c 
#define yf1h4_c  

#define opr_yf1h1_add
#define opr_yf1h2_add
#define opr_yf1h3_add
#define opr_yf1h4_add

#define opr_yf1h1_cut
#define opr_yf1h2_cut
#define opr_yf1h3_cut
#define opr_yf1h4_cut


#define y0h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define y0h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define y0h3_nc  lcd_showstr(16, 3, 6,"right");ls3(time);
#define y0h4_nc  lcd_showstr(16, 4, 6,"right");ls4(time);

#define y0h1_c  ls1(time);
#define y0h2_c 
#define y0h3_c  
#define y0h4_c  

#define opr_y0h1_add
#define opr_y0h2_add
#define opr_y0h3_add
#define opr_y0h4_add

#define opr_y0h1_cut
#define opr_y0h2_cut
#define opr_y0h3_cut
#define opr_y0h4_cut


#define y1h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define y1h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define y1h3_nc  lcd_showstr(16, 3, 6,"right");ls3(time);
#define y1h4_nc  lcd_showstr(16, 4, 6,"right");ls4(time);

#define y1h1_c  
#define y1h2_c  
#define y1h3_c  
#define y1h4_c 

#define opr_y1h1_add
#define opr_y1h2_add
#define opr_y1h3_add
#define opr_y1h4_add

#define opr_y1h1_cut
#define opr_y1h2_cut
#define opr_y1h3_cut
#define opr_y1h4_cut


#define y2h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define y2h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define y2h3_nc  lcd_showstr(16, 3, 6, "right");ls3(time);
#define y2h4_nc  lcd_showstr(16, 4, 6, "right");ls4(time);

#define y2h1_c  
#define y2h2_c  
#define y2h3_c  
#define y2h4_c  

#define opr_y2h1_add
#define opr_y2h2_add
#define opr_y2h3_add
#define opr_y2h4_add

#define opr_y2h1_cut
#define opr_y2h2_cut
#define opr_y2h3_cut
#define opr_y2h4_cut




#define KEY1  GPIO_Pin_2
#define KEY2  GPIO_Pin_3
#define KEY3  GPIO_Pin_4
#define KEY4  GPIO_Pin_5
#define KEY5  GPIO_Pin_6
#define KEY6  GPIO_Pin_0

#define KEY_SET1 GPIO_SetBits(GPIOE,GPIO_Pin_15)
#define KEY_SET2 GPIO_SetBits(GPIOE,GPIO_Pin_14)
#define KEY_SET3 GPIO_SetBits(GPIOE,GPIO_Pin_13)

#define KEY_RESET1 GPIO_ResetBits(GPIOE,GPIO_Pin_15)
#define KEY_RESET2 GPIO_ResetBits(GPIOE,GPIO_Pin_14)
#define KEY_RESET3 GPIO_ResetBits(GPIOE,GPIO_Pin_13)			

#define KEY_SCAN4 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
#define KEY_SCAN5 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)
#define KEY_SCAN6 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)

#include <stdint.h>

int key_scan1(void);
int key_scan2(void);
int key_scan3(int i);

void OLED_Show(void);
void KEY_Init(uint8_t* p_flag_show);//IO初始化
uint8_t KEY_Scan(uint8_t);  	//按键扫描函数					    

#endif


