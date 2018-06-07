
#include "user_gpio.h"
#include "main.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
/********************************* PORTA *************************************/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
/*________________________________ OUTPUT ___________________________________*/
	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIGGER_PIN;	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
/*________________________________ OUTPUT ___________________________________*/
	GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO_PIN;	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
