
#ifndef __KEY_H
#define __KEY_H	 



#include "sys.h"
#define ls0(a) 		lcd_showint16(80,0,a)
#define ls1(a) 		lcd_showint16(80,1,a)
#define ls2(a) 		lcd_showint16(80,2,a)
#define ls3(a) 		lcd_showint16(80,3,a)
#define ls4(a) 		lcd_showint16(80,4,a)
#define ls5(a) 		lcd_showint16(80,5,a)
#define ls6(a) 		lcd_showint16(80,6,a)
#define ls7(a) 		lcd_showint16(80,7,a)
#define ls8(a) 		lcd_showint16(80,8,a)
#define ls9(a) 		lcd_showint16(80,9,a)

#define yf2h0_nc  lcd_showstr(16, 0, 6,"page -2");ls0(time);//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define yf2h1_nc  lcd_showstr(16, 1, 6,"speed1");ls1(time);
#define yf2h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define yf2h3_nc  lcd_showstr(16, 3, 6, "right");ls3(time);
#define yf2h4_nc  lcd_showstr(16, 4, 6, "right");ls4(time);
#define yf2h5_nc  lcd_showstr(16, 5, 6, "right");ls5(time);
#define yf2h6_nc  lcd_showstr(16, 6, 6, "right");ls6(time);
#define yf2h7_nc  lcd_showstr(16, 7, 6, "right");ls7(time);
#define yf2h8_nc  lcd_showstr(16, 8, 6, "right");ls8(time);
#define yf2h9_nc  lcd_showstr(16, 9, 6, "right");ls9(time);
#define yf2h0_c  ls0(time);//页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define yf2h1_c  ls1(time);
#define yf2h2_c  ls2(time);
#define yf2h3_c  ls3(time);
#define yf2h4_c  ls4(time);
#define yf2h5_c  ls5(time);
#define yf2h6_c  ls6(time);
#define yf2h7_c  ls7(time);
#define yf2h8_c  ls8(time);
#define yf2h9_c  ls9(time);
#define opr_yf2h0_add time-=1000  //按下按键时执行的操作 (oprate ye f2 high0)  
#define opr_yf2h1_add
#define opr_yf2h2_add
#define opr_yf2h3_add
#define opr_yf2h4_add
#define opr_yf2h5_add
#define opr_yf2h6_add
#define opr_yf2h7_add
#define opr_yf2h8_add
#define opr_yf2h9_add
#define opr_yf2h0_cut time-=1000  //按下按键时执行的操作 (oprate ye f2 high0)  
#define opr_yf2h1_cut
#define opr_yf2h2_cut
#define opr_yf2h3_cut
#define opr_yf2h4_cut
#define opr_yf2h5_cut
#define opr_yf2h6_cut
#define opr_yf2h7_cut
#define opr_yf2h8_cut
#define opr_yf2h9_cut

#define yf1h0_nc  lcd_showstr(8, 0 , 6,"page -1");ls0(time);//页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define yf1h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define yf1h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define yf1h3_nc  lcd_showstr(16, 3, 6, "right");ls3(time);
#define yf1h4_nc  lcd_showstr(16, 4, 6, "right");ls4(time);
#define yf1h5_nc  lcd_showstr(16, 5, 6, "right");ls5(time);
#define yf1h6_nc  lcd_showstr(16, 6, 6, "right");ls6(time);
#define yf1h7_nc  lcd_showstr(16, 7, 6, "right");ls7(time);
#define yf1h8_nc  lcd_showstr(16, 8, 6, "right");ls8(time);
#define yf1h9_nc  lcd_showstr(16, 9, 6, "right");ls9(time);
#define yf1h0_c  //页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define yf1h1_c  ls1(time);
#define yf1h2_c 
#define yf1h3_c 
#define yf1h4_c  
#define yf1h5_c 
#define yf1h6_c  
#define yf1h7_c  
#define yf1h8_c  
#define yf1h9_c 
#define opr_yf1h0_add time-=1000  //按下按键时执行的操作 (oprate ye fu1 high0)  
#define opr_yf1h1_add
#define opr_yf1h2_add
#define opr_yf1h3_add
#define opr_yf1h4_add
#define opr_yf1h5_add
#define opr_yf1h6_add
#define opr_yf1h7_add
#define opr_yf1h8_add
#define opr_yf1h9_add
#define opr_yf1h0_cut time-=1000  //按下按键时执行的操作 (oprate ye fu1 high0)  
#define opr_yf1h1_cut
#define opr_yf1h2_cut
#define opr_yf1h3_cut
#define opr_yf1h4_cut
#define opr_yf1h5_cut
#define opr_yf1h6_cut
#define opr_yf1h7_cut
#define opr_yf1h8_cut
#define opr_yf1h9_cut

#define y0h0_nc  lcd_showstr(16, 0, 6,"page 0");ls0(time);//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y0h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define y0h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define y0h3_nc  lcd_showstr(16, 3, 6,"right");ls3(time);
#define y0h4_nc  lcd_showstr(16, 4, 6,"right");ls4(time);
#define y0h5_nc  lcd_showstr(16, 5, 6,"right");ls5(time);
#define y0h6_nc  lcd_showstr(16, 6, 6,"right");ls6(time);
#define y0h7_nc  lcd_showstr(16, 7, 6,"right");ls7(time);
#define y0h8_nc  lcd_showstr(16, 8, 6,"right");ls8(time);
#define y0h9_nc  lcd_showstr(16, 9, 6,"right");ls9(time);
#define y0h0_c  //页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define y0h1_c  ls1(time);
#define y0h2_c 
#define y0h3_c  
#define y0h4_c  
#define y0h5_c 
#define y0h6_c  
#define y0h7_c  
#define y0h8_c  
#define y0h9_c  
#define opr_y0h0_add  time-=1000  //按下按键时执行的操作 (oprate ye0 high0)  
#define opr_y0h1_add
#define opr_y0h2_add
#define opr_y0h3_add
#define opr_y0h4_add
#define opr_y0h5_add
#define opr_y0h6_add
#define opr_y0h7_add
#define opr_y0h8_add
#define opr_y0h9_add
#define opr_y0h0_cut  time-=1000  //按下按键时执行的操作 (oprate ye0 high0)  
#define opr_y0h1_cut
#define opr_y0h2_cut
#define opr_y0h3_cut
#define opr_y0h4_cut
#define opr_y0h5_cut
#define opr_y0h6_cut
#define opr_y0h7_cut
#define opr_y0h8_cut
#define opr_y0h9_cut

#define y1h0_nc  lcd_showstr(16, 0, 6,"page 1");ls0(time);//页（ye）1 高度（high）0  不变(即只是按下按键刷新(no change)
#define y1h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define y1h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define y1h3_nc  lcd_showstr(16, 3, 6,"right");ls3(time);
#define y1h4_nc  lcd_showstr(16, 4, 6,"right");ls4(time);
#define y1h5_nc  lcd_showstr(16, 5, 6,"right");ls5(time);
#define y1h6_nc  lcd_showstr(16, 6, 6,"right");ls6(time);
#define y1h7_nc  lcd_showstr(16, 7, 6,"right");ls7(time);
#define y1h8_nc  lcd_showstr(16, 8, 6,"right");ls8(time);
#define y1h9_nc  lcd_showstr(16, 9, 6,"right");ls9(time);
#define y1h0_c  //页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define y1h1_c  ls0(time);
#define y1h2_c  
#define y1h3_c  
#define y1h4_c 
#define y1h5_c  
#define y1h6_c  
#define y1h7_c  
#define y1h8_c  
#define y1h9_c  
#define opr_y1h0_add time-=1000  //按下按键时执行的操作 (oprate ye0 high0)  
#define opr_y1h1_add
#define opr_y1h2_add
#define opr_y1h3_add
#define opr_y1h4_add
#define opr_y1h5_add
#define opr_y1h6_add
#define opr_y1h7_add
#define opr_y1h8_add
#define opr_y1h9_add
#define opr_y1h0_cut time-=1000  //按下按键时执行的操作 (oprate ye0 high0)  
#define opr_y1h1_cut
#define opr_y1h2_cut
#define opr_y1h3_cut
#define opr_y1h4_cut
#define opr_y1h5_cut
#define opr_y1h6_cut
#define opr_y1h7_cut
#define opr_y1h8_cut
#define opr_y1h9_cut

#define y2h0_nc  lcd_showstr(16, 0, 6,"page 2");ls0(time);//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y2h1_nc  lcd_showstr(16, 1, 6,"time");ls1(time);
#define y2h2_nc  lcd_showstr(16, 2, 6,"speed1");ls2(time);
#define y2h3_nc  lcd_showstr(16, 3, 6, "right");ls3(time);
#define y2h4_nc  lcd_showstr(16, 4, 6, "right");ls4(time);
#define y2h5_nc  lcd_showstr(16, 5, 6, "right");ls5(time);
#define y2h6_nc  lcd_showstr(16, 6, 6, "right");ls6(time);
#define y2h7_nc  lcd_showstr(16, 7, 6, "right");ls7(time);
#define y2h8_nc  lcd_showstr(16, 8, 6, "right");ls8(time);
#define y2h9_nc  lcd_showstr(16, 9, 6, "right");ls9(time);
#define y2h0_c  //页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define y2h1_c  ls0(time);
#define y2h2_c  
#define y2h3_c  
#define y2h4_c  
#define y2h5_c  
#define y2h6_c  
#define y2h7_c  
#define y2h8_c  
#define y2h9_c  
#define opr_y2h0_add time-=1000  //按下按键时执行的操作 (oprate ye0 high0)  
#define opr_y2h1_add
#define opr_y2h2_add
#define opr_y2h3_add
#define opr_y2h4_add
#define opr_y2h5_add
#define opr_y2h6_add
#define opr_y2h7_add
#define opr_y2h8_add
#define opr_y2h9_add
#define opr_y2h0_cut
#define opr_y2h1_cut
#define opr_y2h2_cut
#define opr_y2h3_cut
#define opr_y2h4_cut
#define opr_y2h5_cut
#define opr_y2h6_cut
#define opr_y2h7_cut
#define opr_y2h8_cut
#define opr_y2h9_cut



#define KEY1  GPIO_Pin_2
#define KEY2  GPIO_Pin_3
#define KEY3  GPIO_Pin_4
#define KEY4  GPIO_Pin_5
#define KEY5  GPIO_Pin_6
#define KEY6  GPIO_Pin_0

#define KEY_SET1 GPIO_SetBits(GPIOE,KEY1)
#define KEY_SET2 GPIO_SetBits(GPIOE,KEY2)
#define KEY_SET3 GPIO_SetBits(GPIOE,KEY3)

#define KEY_RESET1 GPIO_ResetBits(GPIOE,KEY1)
#define KEY_RESET2 GPIO_ResetBits(GPIOE,KEY2)
#define KEY_RESET3 GPIO_ResetBits(GPIOE,KEY3)			

#define KEY_SCAN4 GPIO_ReadInputDataBit(GPIOE,KEY4)
#define KEY_SCAN5 GPIO_ReadInputDataBit(GPIOE,KEY5)
#define KEY_SCAN6 GPIO_ReadInputDataBit(GPIOC,KEY6)


int key_scan1(void);
int key_scan2(void);
int key_scan3(int i);

void lcd_show(void);
void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    

#endif













//********************************************************************************

//按键驱动代码	  

// K1  -- PA0        K1   按键 --按下后，高电平  
// K2  -- PC13       K2   按键 --按下后，低电平    

//STM32F103工程模板-库函数版本
//DevEBox  大越创新

//淘宝店铺：mcudev.taobao.com
//淘宝店铺：devebox.taobao.com			

//********************************************************************************









