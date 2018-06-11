#include "HCSR501.h"

// Cấu hình cho HCSR501
void HCSR501_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;                   // Khai báo biến khởi tạo
    RCC_APB2PeriphClockCmd(HCSR501_GPIO_RCC_Periph, ENABLE);   
    GPIO_InitStructure.GPIO_Pin = HCSR501_GPIO_Pin;         // Khai báo chân HCSR501
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ;          // Khai báo chế độ 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // Khai báo tần số 50MHz
    GPIO_Init(HCSR501_GPIO_Port, &GPIO_InitStructure);      // Khởi tạo GPIO
}
 
// Hàm đọc GPIO HCSR501
uint8_t HCSR501_GPIO_Read(){
    return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14);
}

/* Hàm đọc HCSR501
   Nếu trong 10us phát hiện chuyển động từ 5us trở lên thì xác nhận có chuyển động */
bool HCSR501_Read_Data(){
    uint8_t HCSR501_temp_cache = 0;
    uint8_t dataAverageCount = 10;
    uint8_t count = 0;
    for(count = 0;count < dataAverageCount;count++){
        delay_us(10);
        HCSR501_temp_cache += HCSR501_GPIO_Read();
    }
    return (HCSR501_temp_cache > dataAverageCount / 2) ? true : false;
}


