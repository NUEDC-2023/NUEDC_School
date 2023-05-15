#include "stm32f10x.h"
#include "OLED.h"
#include "Key.h"
#include "OpenmvComm.h"
#include "Serial.h"

//������ʼ������
int flag_tc;
int point=1;
int time;
void KEY_Init(void) //IO��ʼ��
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);  //ʹ��PE,PCʱ��
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10;             
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //���ó���������
	GPIO_Init(GPIOE, &GPIO_InitStructure);						 
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //IO���ٶ�Ϊ50MHz
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
		
		case 1:{flag_tc--;break;}//��һҳ
		case 2:{point--;break;}//��
		case 3:{flag_tc++;break;}//��һҳ
		case 8:{point++;break;}//��
		
		// case 9:{start2=1;break;}//����ʱ����ִ�а���ɨ�裬δ��������ʱ�رհ���ɨ��
		case 7://֡����ʾ
		{
			lcd_showstr(32,3,5,"frame");
			//lcd_showint8(48, 7, frame1);
			break;
		}
		default://���ҽ��б�������
		{
			switch (flag_tc)
			{
				case 0://��0ҳ
				{
					if(i==4)     //��
					{
						switch (point)//��point��
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					
					if(i==6)  // ��
					{
						switch (point)//��point��
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					break;
				}
				case -1://-1ҳ
				{
					if(i==4)     //��
					{
						switch (point)//��point��
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					
					if(i==6)  // ��
					{
						switch (point)//��point��
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					break;
				}
				
				case 1://-2ҳ
				{
					if(i==4)     //��
					{
						switch (point)//��point��
						{
							case 1:{break;}
							case 2:{break;}
							case 3:{break;}
							case 4:{break;}
							
						}
					}
					
					if(i==6)  // ��
					{
						switch (point)//��point��
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


