#include "sys.h"

/*
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
*/
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct_extiB5;
    NVIC_InitTypeDef NVIC_InitStruct_extiA10;
	NVIC_InitTypeDef NVIC_InitStruct_usart3;
    NVIC_InitTypeDef NVIC_InitStruct_tim2;
    NVIC_InitTypeDef NVIC_InitStruct_tim1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//4级抢占,4级响应。
	
	//外部中断PB5
	NVIC_InitStruct_extiB5.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct_extiB5);
	
    //USART3 NVIC 配置
    NVIC_InitStruct_usart3.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct_usart3.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
	NVIC_InitStruct_usart3.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStruct_usart3.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct_usart3);	//根据指定的参数初始化VIC寄存器
    
    // 定时器2中断
    NVIC_InitStruct_tim2.NVIC_IRQChannel=TIM2_IRQn; //属于TIM2中断
	NVIC_InitStruct_tim2.NVIC_IRQChannelCmd=ENABLE; //中断使能
	NVIC_InitStruct_tim2.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_InitStruct_tim2.NVIC_IRQChannelSubPriority=1; //响应优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_Init(&NVIC_InitStruct_tim2); //根据NVIC_InitStruct_tim1的参数初始化VIC寄存器，设置TIM2中断
    
    //外部中断PA10
	NVIC_InitStruct_extiA10.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct_extiA10.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct_extiA10.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct_extiA10.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct_extiA10);
    
    // 定时器1中断
    NVIC_InitStruct_tim1.NVIC_IRQChannel=TIM1_UP_IRQn; //属于TIM1中断
	NVIC_InitStruct_tim1.NVIC_IRQChannelCmd=ENABLE; //中断使能
	NVIC_InitStruct_tim1.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_InitStruct_tim1.NVIC_IRQChannelSubPriority=2; //响应优先级为1级，值越小优先级越高，0级优先级最高
	NVIC_Init(&NVIC_InitStruct_tim1); //根据NVIC_InitStruct_tim1的参数初始化VIC寄存器，设置TIM2中断
}