#include "uart.h"

void USART1_Configuration(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);
	
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //¸´ÓÃÍÆÍìÊä³ö
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  	/* Configure USART1 Rx (PA.10) as input floating */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //¸¡¿ÕÊäÈë
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate            = 9600  ;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; //8¸öÊý¾ÝÎ»
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;    //1¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity              = USART_Parity_No ;    //ÎÞÆæÅ¼Ð£Ñé
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//½ûÓÃÓ²¼þÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;//Ê¹ÄÜ·¢ËÍ/½ÓÊÕ
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//Enable Interrupt
	USART_Cmd(USART1, ENABLE);     

}

void USART_SendChar(USART_TypeDef* USARTx, u8 data)
{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
		USART_SendData(USARTx,data);
	
}

void USART_SendString(USART_TypeDef* USARTx, char*str)
{
	   while (*str)
   { 
		 USART_SendChar(USARTx,*str); 
     str++;
   }
}

void UART_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			  //ÖÐ¶Ï·Ö×é2

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 		  //USART1½ÓÊÕÖÐ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //ÏÈÕ¼ÓÅÏÈ¼¶0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //´ÎÕ¼ÓÅÏÈ¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
