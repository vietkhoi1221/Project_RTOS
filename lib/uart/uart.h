#ifndef __UART_H
#define __UART_H

#include "uart.h"
#include "stm32f10x.h"	   
#include "stm32f10x_gpio.h"

void USART1_Configuration(void);

void USART_SendChar(USART_TypeDef* USARTx, u8 data);

void USART_SendString(USART_TypeDef* USARTx, char*str);

void UART_NVIC_Configuration(void);

#endif
