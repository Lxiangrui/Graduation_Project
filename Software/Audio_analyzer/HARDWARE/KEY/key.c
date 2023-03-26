#include "key.h"
#include "delay.h"
void key_Init()
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);
		EXTI_InitStructure.EXTI_Line = EXTI_Line1;
		EXTI_Init(&EXTI_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_Init(&NVIC_InitStructure);
		
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
		EXTI_InitStructure.EXTI_Line = EXTI_Line2;
		EXTI_Init(&EXTI_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_Init(&NVIC_InitStructure);
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
		EXTI_InitStructure.EXTI_Line = EXTI_Line3;
		EXTI_Init(&EXTI_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_Init(&NVIC_InitStructure);
		
}


