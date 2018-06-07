#include "HCSR04.h"

float HCSR04_Read(void) 
   {
uint32_t time, timeout;
float dis;
/* Trigger low */
 //HCSR04_TRIGGER_LOW;
	GPIO_WriteBit(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN,Bit_RESET);
		 
/* delay_us 2 us */
delay_us(2);
/* Trigger high for 10us */
//HCSR04_TRIGGER_HIGH;
		 GPIO_WriteBit(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN,Bit_SET);
/* delay_us 10 us */
delay_us(10);
/* Trigger low */
//HCSR04_TRIGGER_LOW;
		  GPIO_WriteBit(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN,Bit_RESET);

/* Give some time for response */
timeout = HCSR04_TIMEOUT;
while (HCSR04_ECHO_CHECK == Bit_RESET) 
   {
if (timeout-- == 0x00) 
   {
   
   
return -1;
}
}

/* Start time */
//time = 0;
TIM_SetCounter(TIM4,0);

/* Wait till signal is low */
while (HCSR04_ECHO_CHECK == Bit_SET) 
   {
/* Increase time */
//time++;
		 time=TIM_GetCounter(TIM4);
/* delay_us 1us */
//delay_us(1);
}

/* Convert us to cm */
dis = (float)time* HCSR04_NUMBER/2;// /58 ;//
/* Return distance */
return dis;
}
