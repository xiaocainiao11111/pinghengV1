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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//4??????,4????????
	
	//????????PB5
	NVIC_InitStruct_extiB5.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct_extiB5);
	
    //USART3 NVIC ????
    NVIC_InitStruct_usart3.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct_usart3.NVIC_IRQChannelPreemptionPriority=1 ;//??????????3
	NVIC_InitStruct_usart3.NVIC_IRQChannelSubPriority = 0;		//????????3
	NVIC_InitStruct_usart3.NVIC_IRQChannelCmd = ENABLE;			//IRQ????????
	NVIC_Init(&NVIC_InitStruct_usart3);	//????????????????????VIC??????
    
    // ??????2????
    NVIC_InitStruct_tim2.NVIC_IRQChannel=TIM2_IRQn; //????TIM2????
	NVIC_InitStruct_tim2.NVIC_IRQChannelCmd=ENABLE; //????????
	NVIC_InitStruct_tim2.NVIC_IRQChannelPreemptionPriority=1; //????????????1??????????????????????0????????????
	NVIC_InitStruct_tim2.NVIC_IRQChannelSubPriority=1; //????????????1??????????????????????0????????????
	NVIC_Init(&NVIC_InitStruct_tim2); //????NVIC_InitStruct_tim1????????????VIC????????????TIM2????
    
    //????????PA10
	NVIC_InitStruct_extiA10.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct_extiA10.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct_extiA10.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct_extiA10.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct_extiA10);
    
    // ??????1????
    NVIC_InitStruct_tim1.NVIC_IRQChannel=TIM1_UP_IRQn; //????TIM1????
	NVIC_InitStruct_tim1.NVIC_IRQChannelCmd=ENABLE; //????????
	NVIC_InitStruct_tim1.NVIC_IRQChannelPreemptionPriority=2; //????????????1??????????????????????0????????????
	NVIC_InitStruct_tim1.NVIC_IRQChannelSubPriority=2; //????????????1??????????????????????0????????????
	NVIC_Init(&NVIC_InitStruct_tim1); //????NVIC_InitStruct_tim1????????????VIC????????????TIM2????
}