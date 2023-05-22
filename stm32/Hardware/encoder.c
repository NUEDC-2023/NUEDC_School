//#include "headfile.h"
#include "stm32f10x.h"

int speed1,speed2,distance1,distance2;

/* RCC时钟配置 */
void RCC_config(void)
{ 
    ErrorStatus HSEStartUpStatus;
 
    /* RCC寄存器设置为默认配置 */
    RCC_DeInit();
    /* 打开外部高速时钟 */
    RCC_HSEConfig(RCC_HSE_ON);
    /* 等待外部高速时钟稳定 */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStartUpStatus == SUCCESS) 
    { 
        /* 设置HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        /* 设置PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        /* 设置PCLK1 = HCLK / 2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);
//        /* 设置FLASH代码延时 */
//        FLASH_SetLatency(FLASH_Latency_2);
//        /* 使能预取址缓存 */
//        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        /* 设置PLL时钟源为HSE倍频9 72MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        /* 使能PLL */
        RCC_PLLCmd(ENABLE);
        /* 等待PLL稳定 */
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        /* 设置PLL为系统时钟源 */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        /* 等待系统时钟源切换到PLL */
        while(RCC_GetSYSCLKSource() != 0x08);
    }
}
 
/* GPIO配置 */
void TIMER_config1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 使能GPIOA时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    //GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
	  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //禁止JTAG功能，把PB3，PA15作为普通IO口使用  

    /* 将GPIOA时钟设置为默认参数 */
    GPIO_DeInit(GPIOA);    
    
    /* 浮空输入 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    /* 第3引脚 */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
	  //  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;

    /* 初始化GPIOA */
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    
    /* 允许TIM2的时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    /* 将定时器2寄存器设为初始值 */
    TIM_DeInit(TIM2);
 
    /* 填入缺省值 */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    /* 预分频值 */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    /* 自动重载值 */
    TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
    /* 时钟分割 */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /* 向上计数 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    /* 初始化定时器2 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 
    /* 设置编码器模式 */
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);
    
    /* 填入缺省值 */
    TIM_ICStructInit(&TIM_ICInitStructure);
    /* 输入比较滤波器 */
    TIM_ICInitStructure.TIM_ICFilter = 6;
    /* 初始化定时器2 */
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
 
    /* 计数器初始化 */
    TIM_SetCounter(TIM2, 0);
 
    /* 开启定时器2 */
    TIM_Cmd(TIM2, ENABLE);
}
void TIMER_config2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* 使能GPIOA时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    
    /* 将GPIOA时钟设置为默认参数 */
    
    /* 浮空输入 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    /* 第3引脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    /* 初始化GPIOB */
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    
    /* 允许TIM2的时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 
    /* 将定时器2寄存器设为初始值 */
    TIM_DeInit(TIM4);
 
    /* 填入缺省值 */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    /* 预分频值 */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    /* 自动重载值 */
    TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
    /* 时钟分割 */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /* 向上计数 */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    /* 初始化定时器2 */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
    /* 设置编码器模式 */
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);
    
    /* 填入缺省值 */
    TIM_ICStructInit(&TIM_ICInitStructure);
    /* 输入比较滤波器 */
    TIM_ICInitStructure.TIM_ICFilter = 6;
    /* 初始化定时器2 */
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
    /* 计数器初始化 */
    TIM_SetCounter(TIM4, 0);
 
    /* 开启定时器2 */
    TIM_Cmd(TIM4, ENABLE);
}


/**************************************************************************
函数功能：单位时间读取编码器A计数
入口参数：无
返回  值：计数值
**************************************************************************/
void Read_EncoderA(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM= (short)TIM2 -> CNT;  
	speed1=Encoder_TIM;
	distance1+=speed1-0;
	
	TIM2 -> CNT=0;
	
	return ;
}
/**************************************************************************
函数功能：单位时间读取编码器B计数
入口参数：无
返回  值：计数值
**************************************************************************/
void Read_EncoderB(void)
{
	int Encoder_TIM = 0;  
	Encoder_TIM= (short)TIM4 -> CNT; 
  speed2=Encoder_TIM;
	distance2+=speed2-0;

	TIM4 -> CNT=0;
	return ;
}

/**************************************************************************
*  函数功能：TIM2中断服务函数
*
*  入口参数：无
*
*  返 回 值：无
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}


/**************************************************************************
*  函数功能：TIM3中断服务函数
*
*  入口参数：无
*
*  返 回 值：无
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
