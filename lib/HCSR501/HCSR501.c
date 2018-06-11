#include "HCSR501.h"

       
//LED IO???
void HCSR501_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(HCSR501_GPIO_RCC_Periph, ENABLE);    //??PB,PE????

    GPIO_InitStructure.GPIO_Pin = HCSR501_GPIO_Pin;             //LED0-->PB.5 ????
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ;        //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //IO????50MHz
    GPIO_Init(HCSR501_GPIO_Port, &GPIO_InitStructure);                //?????????GPIOB.5
}
 
uint8_t HCSR501_GPIO_Read()
{
    return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14);
}

bool HCSR501_Read_Data()
{
    uint8_t HCSR501_temp_cache = 0;
    uint8_t dataAverageCount = 10;
    uint8_t count = 0;
    for(count = 0;count < dataAverageCount;count++)
    {
        delay_us(10);
        HCSR501_temp_cache += HCSR501_GPIO_Read();
    }
    return (HCSR501_temp_cache > dataAverageCount / 2) ? true : false;
}


