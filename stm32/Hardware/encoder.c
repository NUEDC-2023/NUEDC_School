//#include "headfile.h"
#include "stm32f10x.h"

int speed1,speed2,distance1,distance2;

/* RCCʱ������ */
void RCC_config(void)
{ 
    ErrorStatus HSEStartUpStatus;
 
    /* RCC�Ĵ�������ΪĬ������ */
    RCC_DeInit();
    /* ���ⲿ����ʱ�� */
    RCC_HSEConfig(RCC_HSE_ON);
    /* �ȴ��ⲿ����ʱ���ȶ� */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStartUpStatus == SUCCESS) 
    { 
        /* ����HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        /* ����PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        /* ����PCLK1 = HCLK / 2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);
//        /* ����FLASH������ʱ */
//        FLASH_SetLatency(FLASH_Latency_2);
//        /* ʹ��Ԥȡַ���� */
//        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        /* ����PLLʱ��ԴΪHSE��Ƶ9 72MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        /* ʹ��PLL */
        RCC_PLLCmd(ENABLE);
        /* �ȴ�PLL�ȶ� */
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        /* ����PLLΪϵͳʱ��Դ */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        /* �ȴ�ϵͳʱ��Դ�л���PLL */
        while(RCC_GetSYSCLKSource() != 0x08);
    }
}
 
/* GPIO���� */
void TIMER_config1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* ʹ��GPIOAʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    //GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
	  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //��ֹJTAG���ܣ���PB3��PA15��Ϊ��ͨIO��ʹ��  

    /* ��GPIOAʱ������ΪĬ�ϲ��� */
    GPIO_DeInit(GPIOA);    
    
    /* �������� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    /* ��3���� */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
	  //  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;

    /* ��ʼ��GPIOA */
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    
    /* ����TIM2��ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    /* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */
    TIM_DeInit(TIM2);
 
    /* ����ȱʡֵ */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    /* Ԥ��Ƶֵ */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    /* �Զ�����ֵ */
    TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
    /* ʱ�ӷָ� */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /* ���ϼ��� */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    /* ��ʼ����ʱ��2 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 
    /* ���ñ�����ģʽ */
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);
    
    /* ����ȱʡֵ */
    TIM_ICStructInit(&TIM_ICInitStructure);
    /* ����Ƚ��˲��� */
    TIM_ICInitStructure.TIM_ICFilter = 6;
    /* ��ʼ����ʱ��2 */
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
 
    /* ��������ʼ�� */
    TIM_SetCounter(TIM2, 0);
 
    /* ������ʱ��2 */
    TIM_Cmd(TIM2, ENABLE);
}
void TIMER_config2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* ʹ��GPIOAʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    
    /* ��GPIOAʱ������ΪĬ�ϲ��� */
    
    /* �������� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    /* ��3���� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    /* ��ʼ��GPIOB */
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    
    /* ����TIM2��ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 
    /* ����ʱ��2�Ĵ�����Ϊ��ʼֵ */
    TIM_DeInit(TIM4);
 
    /* ����ȱʡֵ */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    /* Ԥ��Ƶֵ */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    /* �Զ�����ֵ */
    TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
    /* ʱ�ӷָ� */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    /* ���ϼ��� */
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    /* ��ʼ����ʱ��2 */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
    /* ���ñ�����ģʽ */
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);
    
    /* ����ȱʡֵ */
    TIM_ICStructInit(&TIM_ICInitStructure);
    /* ����Ƚ��˲��� */
    TIM_ICInitStructure.TIM_ICFilter = 6;
    /* ��ʼ����ʱ��2 */
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
    /* ��������ʼ�� */
    TIM_SetCounter(TIM4, 0);
 
    /* ������ʱ��2 */
    TIM_Cmd(TIM4, ENABLE);
}


/**************************************************************************
�������ܣ���λʱ���ȡ������A����
��ڲ�������
����  ֵ������ֵ
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
�������ܣ���λʱ���ȡ������B����
��ڲ�������
����  ֵ������ֵ
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
*  �������ܣ�TIM2�жϷ�����
*
*  ��ڲ�������
*
*  �� �� ֵ����
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}


/**************************************************************************
*  �������ܣ�TIM3�жϷ�����
*
*  ��ڲ�������
*
*  �� �� ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
