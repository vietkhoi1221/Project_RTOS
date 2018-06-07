
#ifndef HCSR04_H
#define HCSR04_H 110
/**
* Library dependencies
* - STM32F4xx
* - STM32F4xx RCC
* - STM32F4xx GPIO
* - defines.h
* - TM DELAY
*/
/**
* Includes
*/

#include<stm32f10x_adc.h>
#include "HCSR04.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "user_delay.h"

/* Trigger PIN */
#ifndef HCSR04_TRIGGER_PIN
#define HCSR04_TRIGGER_RCC RCC_APB2Periph_GPIOB      
#define HCSR04_TRIGGER_PORT GPIOB 
#define HCSR04_TRIGGER_PIN GPIO_Pin_14
#endif

/* Echo PIN */
#ifndef HCSR04_ECHO_PIN
#define HCSR04_ECHO_RCC RCC_APB2Periph_GPIOB 
#define HCSR04_ECHO_PORT GPIOB
#define HCSR04_ECHO_PIN GPIO_Pin_15
#endif

/* Default timeout pulses */
#ifndef HCSR04_TIMEOUT
#define HCSR04_TIMEOUT 1000000
#endif

/* Pin operations */
#define HCSR04_TRIGGER_LOW HCSR04_TRIGGER_PORT->CRH = HCSR04_TRIGGER_PIN
//#define HCSR04_TRIGGER_LOW SET
//#define HCSR04_TRIGGER_HIGH RESET

#define HCSR04_TRIGGER_HIGH HCSR04_TRIGGER_PORT->CRL = HCSR04_TRIGGER_PIN
#define HCSR04_ECHO_CHECK GPIO_ReadInputDataBit(HCSR04_ECHO_PORT, HCSR04_ECHO_PIN)

/* Time to cm */
#define HCSR04_NUMBER ((float)0.027) //(1s/58)=0.0171821

/**
* Initialize HC-SR04 sensor
* 
* Returns 1 if sensor is ready to use, or 0 if not
*/
extern uint8_t HCSR04_Init(void);

/**
* Start sensor measurement and read it's data
* 
* This function returns -1 if there was an error, or distance in cm if everything is OK
*/

extern float HCSR04_Read(void);
#endif
