#include "stm32f10x.h"
#include "OLED.h"
#include "Key.h"
#include "OpenmvComm.h"
#include "Serial.h"

//按键初始化函数
int flag_tc;
int point=1;
int time;
void KEY_Init(void) //IO初始化
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);  //使能PE,PC时钟
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10;             
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //设置成上拉输入
	GPIO_Init(GPIOE, &GPIO_InitStructure);						 
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);		
}

int key_scan1(void)
{
	if(KEY_SCAN4==1)return 1;
	if(KEY_SCAN5==1)return 2;
	if(KEY_SCAN6==1)return 3;
	return 0;
}
int key_scan2(void)
{
	int i=0;
	KEY_SET1;
	KEY_RESET2;
	KEY_RESET3;
	
	i=key_scan1();
	switch(i)
	{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		default:break;
	}
	KEY_RESET1;
	KEY_SET2;
	i=key_scan1();
	switch(i)
	{
		case 1: return 4;
		case 2: return 5;
		case 3: return 6;
		default:break;
	}
	KEY_RESET2;
	KEY_SET3;
	i=key_scan1();
	switch(i)
	{
		case 1: return 7;
		case 2: return 8;
		case 3: return 9;
		default:break;
	}
	KEY_RESET1;
	KEY_RESET2;
	KEY_RESET3;
	
	return 0;
}
int key_scan3(int i)
{
	switch(i)
	{
		case 0:return 0;
		
		case 1:{flag_tc--;break;}//上一页
		case 2:{point--;break;}//上
		case 3:{flag_tc++;break;}//下一页
		case 8:{point++;break;}//下
		
		// case 9:{start2=1;break;}//启动时依旧执行按键扫描，未按下启动时关闭按键扫描
		case 7://帧率显示
		{
			lcd_showstr(32,3,5,"frame");
			//lcd_showint8(48, 7, frame1);
			break;
		}
		default://左右进行变量增减
		{
			switch (flag_tc)
			{
				case 0://第0页
				{
					if(i==4)     //左
					{
						switch (point)//第point行
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					
					if(i==6)  // 右
					{
						switch (point)//第point行
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					break;
				}
				case -1://-1页
				{
					if(i==4)     //左
					{
						switch (point)//第point行
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					
					if(i==6)  // 右
					{
						switch (point)//第point行
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					break;
				}
				
				case 1://-2页
				{
					if(i==4)     //左
					{
						switch (point)//第point行
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					
					if(i==6)  // 右
					{
						switch (point)//第point行
						{
							case 1:{opr_y1h1_add;break;}
							case 2:{opr_y1h2_add;break;}
							case 3:{opr_y1h3_add;break;}
							case 4:{opr_y1h4_add;break;}
							
						}
					}
					break;
				}
			}
		}
	}
	if(i!=9)
	{
		
	}
	return 1;
}
void lcd_show(void)
{
	static int start=0;
	if(start==0)
	{
	
	}
	OLED_Clear();
	OLED_ShowChar(point,1,'-');
	static int flag1=0;
	static int j;
	int i=key_scan2();
	j++;
	if((flag1==0)&&i)
	{
		flag1=1;
		key_scan3(i);
	}
	else flag1=i;
	
	if(flag_tc==-1)
	{
		
	}
	else if(flag_tc==0)
	{
		//OLED_ShowSignedNum(1,9,11,4);
		//OLED_ShowSignedNum(2,9,12,4);
		//OLED_ShowSignedNum(3,9,13,4);
		//OLED_ShowSignedNum(4,9,14,4);
		OpenMV_Display_Specs();
	}
	else if(flag_tc==1)
	{
		y1h1_c;
		y1h2_c;
		y1h3_c;
		y1h4_c;
		
	}
}


