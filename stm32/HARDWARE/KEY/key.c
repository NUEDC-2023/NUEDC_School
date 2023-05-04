
#include "headfile.h"
					    
//按键初始化函数
int flag_tc;
int point;
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC,ENABLE);  //使能PE,PC时钟
	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_5|GPIO_Pin_6;             
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);						 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
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
                            case 0:{opr_y0h0_cut;break;}
                            case 1:{opr_y0h1_cut;break;}
                            case 2:{opr_y0h2_cut;break;}
                            case 3:{opr_y0h3_cut;break;}
                            case 4:{opr_y0h4_cut;break;}
                            case 5:{opr_y0h5_cut;break;}
                            case 6:{opr_y0h6_cut;break;}
                            case 7:{opr_y0h7_cut;break;}
														case 8:{opr_y0h8_cut;break;}
                            case 9:{opr_y0h9_cut;break;}
                        }
                    }

                    if(i==6)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 0:{opr_y0h0_add;break;}
                            case 1:{opr_y0h1_add;break;}
                            case 2:{opr_y0h2_add;break;}
                            case 3:{opr_y0h3_add;break;}
                            case 4:{opr_y0h4_add;break;}
                            case 5:{opr_y0h5_add;break;}
                            case 6:{opr_y0h6_add;break;}
                            case 7:{opr_y0h7_add;break;}
														case 8:{opr_y0h8_add;break;}
                            case 9:{opr_y0h9_add;break;}
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
	                          case 0:{opr_yf1h0_cut;break;}
                            case 1:{opr_yf1h1_cut;break;}
                            case 2:{opr_yf1h2_cut;break;}
                            case 3:{opr_yf1h3_cut;break;}
                            case 4:{opr_yf1h4_cut;break;}
                            case 5:{opr_yf1h5_cut;break;}
                            case 6:{opr_yf1h6_cut;break;}
                            case 7:{opr_yf1h7_cut;break;}
														case 8:{opr_yf1h8_cut;break;}
                            case 9:{opr_yf1h9_cut;break;}
                         }
                     }

                     if(i==6)  // 右
                     {
                         switch (point)//第point行
                         {
                            case 0:{opr_yf1h0_add;break;}
                            case 1:{opr_yf1h1_add;break;}
                            case 2:{opr_yf1h2_add;break;}
                            case 3:{opr_yf1h3_add;break;}
                            case 4:{opr_yf1h4_add;break;}
                            case 5:{opr_yf1h5_add;break;}
                            case 6:{opr_yf1h6_add;break;}
                            case 7:{opr_yf1h7_add;break;}
														case 8:{opr_yf1h8_add;break;}
                            case 9:{opr_yf1h9_add;break;}
                         }
                     }
                     break;
                }
                case -2://-2页
                {
                    if(i==4)     //左
                    {
                        switch (point)//第point行
                        {
                            case 0:{opr_yf2h0_cut;break;}
                            case 1:{opr_yf2h1_cut;break;}
                            case 2:{opr_yf2h2_cut;break;}
                            case 3:{opr_yf2h3_cut;break;}
                            case 4:{opr_yf2h4_cut;break;}
                            case 5:{opr_yf2h5_cut;break;}
                            case 6:{opr_yf2h6_cut;break;}
                            case 7:{opr_yf2h7_cut;break;}
														case 8:{opr_yf2h8_cut;break;}
                            case 9:{opr_yf2h9_cut;break;}
                        }
                    }

                    if(i==6)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 0:{opr_yf2h0_add;break;}
                            case 1:{opr_yf2h1_add;break;}
                            case 2:{opr_yf2h2_add;break;}
                            case 3:{opr_yf2h3_add;break;}
                            case 4:{opr_yf2h4_add;break;}
                            case 5:{opr_yf2h5_add;break;}
                            case 6:{opr_yf2h6_add;break;}
                            case 7:{opr_yf2h7_add;break;}
														case 8:{opr_yf2h8_add;break;}
                            case 9:{opr_yf2h9_add;break;}
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
                            case 0:{opr_y1h0_cut;break;}
                            case 1:{opr_y1h1_cut;break;}
                            case 2:{opr_y1h2_cut;break;}
                            case 3:{opr_y1h3_cut;break;}
                            case 4:{opr_y1h4_cut;break;}
                            case 5:{opr_y1h5_cut;break;}
                            case 6:{opr_y1h6_cut;break;}
                            case 7:{opr_y1h7_cut;break;}
														case 8:{opr_y1h8_cut;break;}
                            case 9:{opr_y1h9_cut;break;}
                        }
                    }

                    if(i==6)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 0:{opr_y1h0_add;break;}
                            case 1:{opr_y1h1_add;break;}
                            case 2:{opr_y1h2_add;break;}
                            case 3:{opr_y1h3_add;break;}
                            case 4:{opr_y1h4_add;break;}
                            case 5:{opr_y1h5_add;break;}
                            case 6:{opr_y1h6_add;break;}
                            case 7:{opr_y1h7_add;break;}
														case 8:{opr_y1h8_add;break;}
                            case 9:{opr_y1h9_add;break;}
                        }
                    }
                    break;
                }
								case 2://2页
                {
                    if(i==4)     //左
                    {
                        switch (point)//第point行
                        {
                            case 0:{opr_y2h0_cut;break;}
                            case 1:{opr_y2h1_cut;break;}
                            case 2:{opr_y2h2_cut;break;}
                            case 3:{opr_y2h3_cut;break;}
                            case 4:{opr_y2h4_cut;break;}
                            case 5:{opr_y2h5_cut;break;}
                            case 6:{opr_y2h6_cut;break;}
                            case 7:{opr_y2h7_cut;break;}
														case 8:{opr_y2h8_cut;break;}
                            case 9:{opr_y2h9_cut;break;}
                        }
                    }

                    if(i==6)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 0:{opr_y2h0_add;break;}
                            case 1:{opr_y2h1_add;break;}
                            case 2:{opr_y2h2_add;break;}
                            case 3:{opr_y2h3_add;break;}
                            case 4:{opr_y2h4_add;break;}
                            case 5:{opr_y2h5_add;break;}
                            case 6:{opr_y2h6_add;break;}
                            case 7:{opr_y2h7_add;break;}
														case 8:{opr_y2h8_add;break;}
                            case 9:{opr_y2h9_add;break;}
                        }
                    }
                    break;
                }
            }
        }
    }
    if(i!=9)
    {
        switch(flag_tc)
        {
            case -2://-2页
            {
                LCD_Clear(WHITE);
                lcd_showstr(0, point,1, "-");
								yf2h0_nc;
								yf2h1_nc;
								yf2h2_nc;
								yf2h3_nc;
								yf2h4_nc;
								yf2h5_nc;
								yf2h6_nc;
								yf2h7_nc;
								yf2h8_nc;
								yf2h9_nc;
                break;
            }
            case -1://-1页
            {
                LCD_Clear(WHITE);
                lcd_showstr(0, point,1, "-");
								yf1h0_nc;							
								yf1h1_nc;
								yf1h2_nc;
								yf1h3_nc;
								yf1h4_nc;
								yf1h5_nc;
								yf1h6_nc;
								yf1h7_nc;
								yf1h8_nc;
								yf1h9_nc;

                break;
            }
            case 0://0页
            {
                LCD_Clear(WHITE);
                lcd_showstr(0, point,1, "-");
								y0h0_nc;
								y0h1_nc;
								y0h2_nc;
								y0h3_nc;
								y0h4_nc;
								y0h5_nc;
								y0h6_nc;
								y0h7_nc;
								y0h8_nc;
								y0h9_nc;
                break;
            }
            case 1://1页
            {
                LCD_Clear(WHITE);
                lcd_showstr(0, point,1, "-");
								y1h0_nc;
								y1h1_nc;
								y1h2_nc;
								y1h3_nc;
								y1h4_nc;
								y1h5_nc;
								y1h6_nc;
								y1h7_nc;
								y1h8_nc;
								y1h9_nc;
                break;
            }
            case 2://2页
            {
                LCD_Clear(WHITE);
                lcd_showstr(0, point,1, "-");
								y2h0_nc;
								y2h1_nc;
								y2h2_nc;
								y2h3_nc;
								y2h4_nc;
								y2h5_nc;
								y2h6_nc;
								y2h7_nc;
								y2h8_nc;
								y2h9_nc;
                break;
            }
            default:
            {
                LCD_Clear(WHITE);
            }
        }
    }
    return 1;
}
void lcd_show(void)
{
		static int start=0;
		if(start==0)
		{
			y0h0_nc;
			y0h1_nc;
			y0h2_nc;
			y0h3_nc;
			y0h4_nc;
			y0h5_nc;
			y0h6_nc;
			y0h7_nc;
			y0h8_nc;
			y0h9_nc;
			start=1;
		}
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
    //以上为按键扫描部分

    //以下为lcd显示变量部分
  //  if(j%10==0)
  //  {
        if(flag_tc==-2)
        {
					yf2h0_c;
					yf2h1_c;
					yf2h2_c;
					yf2h3_c;
					yf2h4_c;
					yf2h5_c;
					yf2h6_c;
					yf2h7_c;
					yf2h8_c;
					yf2h9_c;
        }
        else if(flag_tc==-1)
        {
										yf1h0_c;
					yf1h1_c;
					yf1h2_c;
					yf1h3_c;
					yf1h4_c;
					yf1h5_c;
					yf1h6_c;
					yf1h7_c;
					yf1h8_c;
					yf1h9_c;
        }
        else if(flag_tc==0)
        {
					y0h0_c;
					y0h1_c;
					y0h2_c;
					y0h3_c;
					y0h4_c;
					y0h5_c;
					y0h6_c;
					y0h7_c;
					y0h8_c;
					y0h9_c;
        }
				else if(flag_tc==1)
        {
					y1h0_c;
					y1h1_c;
					y1h2_c;
					y1h3_c;
					y1h4_c;
					y1h5_c;
					y1h6_c;
					y1h7_c;
					y1h8_c;
					y1h9_c;
        }
				else if(flag_tc==2)
        {
					y2h0_c;
					y2h1_c;
					y2h2_c;
					y2h3_c;
					y2h4_c;
					y2h5_c;
					y2h6_c;
					y2h7_c;
					y2h8_c;
					y2h9_c;
        }
   // }

}











