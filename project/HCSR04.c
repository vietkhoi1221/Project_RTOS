#include "HCSR04.h"

// Hàm đọc HCSR04
float HCSR04_Read(void){
    uint32_t time, timeout;
    float dis;
    //Cho chân Trigger xuống mức thấp trong 2us
	GPIO_WriteBit(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN,Bit_RESET);
    delay_us(2);
    // Kéo chân Trigger lên mức cao trong 10us
	GPIO_WriteBit(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN,Bit_SET);
    delay_us(10);
    // Cho chân Trigger xuống mức thấp
	GPIO_WriteBit(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN,Bit_RESET);

    /* Nhận thời gian mà sóng âm trả về*/
    timeout = HCSR04_TIMEOUT;
    while (HCSR04_ECHO_CHECK == Bit_RESET){
        if (timeout-- == 0x00){
            return -1;
        }
    }

    // Khởi tạo timer4
    TIM_SetCounter(TIM4,0);

    /* Chờ chân echo bằng 0, trong thời gian đó đọc giá trị timer4 */
    while (HCSR04_ECHO_CHECK == Bit_SET){
        time=TIM_GetCounter(TIM4);
    }
    // Tính khoảng cách, chia 2 vì có 2 lượt đi và về
    dis = (float)time* HCSR04_NUMBER/2;
    /* Trả về dis */
    return dis;
}
