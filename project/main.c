//Khai báo thư viện
#include "stm32f10x.h"
#include "i2c_lcd.h" 
#include "main.h"
//Khai báo biến
int kc;
bool a=true;
char distance[5];
uint32_t Time_ST=0;							//Biến delay bằng system tick timer	

GPIO_InitTypeDef 					GPIO_InitStructure;		// Khai báo biến để cấu hình GPIO
I2C_InitTypeDef						I2C_InitStructure;		// Khai báo biến để sử dụng thư viện chuẩn I2C của ST.

void GPIO_Configuration(void);				// Hàm cấu hình GPIO
void Delay_ms(uint16_t time);				// Hàm delay
void Delay_msST(uint16_t nTime);			// Hàm delay bằng system tick timer
void I2C_LCD_Configuration(void);			// Chương trình con cấu hình I2C
void cauhinhTIMER(){    														// ts 72mhz, chia trc 72=> 1tr xung = 1s => 1xung = 1us     
	TIM_TimeBaseInitTypeDef   TM;        
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM4, ENABLE );     
	TM.TIM_ClockDivision =0;         						// Không chia xung   
	TM.TIM_CounterMode = TIM_CounterMode_Up ;         		// đếm lên  
	TM.TIM_Period = 9999;									// Giá trị tự động nạp lại là 9999       
	TM.TIM_Prescaler = 71;         							// bộ chia trước 72      
	TM.TIM_RepetitionCounter =0;         					// báo ngắt khi tràn        
	TIM_TimeBaseInit (TIM4,&TM);        
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );        
	TIM_Cmd(TIM4,ENABLE ); 
}
// Viết hàm cấu hình cho chân 13 PORTC
void cauhinh(){
	GPIO_InitTypeDef gpio;									//Khai báo biến gpio
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 	// Cấp xung clock cho PORT C
	gpio.GPIO_Pin = GPIO_Pin_13; 							// Chọn chân 13 của PORT C
	gpio.GPIO_Mode = GPIO_Mode_Out_PP; 						// Chọn chế độ cho chân 13 là PORT C
	gpio.GPIO_Speed = GPIO_Speed_50MHz; 					// Chọn tốc độ cho chân 13 là 50MHz
	GPIO_Init(GPIOC,&gpio);									// Khởi tạo GPIO PORTC 
}

// Hàm chình
int main(void){
	SystemInit();								// Khởi tạo hệ thống
	SysTick_Config(SystemCoreClock/1000);		// cấu hình system tick timer
	GPIO_Configuration();						// Cấu hình GPIO
	I2C_LCD_Configuration();					// cấu hình LCD I2C
	lcd_init ();   								// Khởi tạo LCD
	delay_init(72);								// Khởi tạo các hàm delay_us và delay_ms
	cauhinhTIMER();								// cấu hình Timer
	cauhinh();									// cấu hình GPIO
	HCSR501_Init();								// Khởi tạo PIR
	HCSR501_GPIO_Read();						// Đọc PIR
	USART1_Configuration();						// cấu hình UART1

	while (1){
			a =HCSR501_Read_Data();							// Đọc PIR
			if (a==true)									// nếu có chuyển động	
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET); 	// Xuất mức 1 ra pin 13															
			else
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET); // Xuất mức 0 ra pin 13	
			// Tiến hành kéo nhả chân trigger của HC-SR04 để nhận dữ liệu
			GPIO_WriteBit(GPIOB,HCSR04_TRIGGER_PIN,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,HCSR04_TRIGGER_PIN)));
			Delay_ms(100);									// Delay 100ms
			kc = HCSR04_Read();								// Đọc cảm biến HC-SR04
			// tiến hành chuyển số thành xâu để hiện lên LCD
			if (kc < 10)
				sprintf(distance,"%d  ",kc);
			else if (kc < 100)
				sprintf(distance,"%d ",kc);
			else 
				sprintf(distance,"%d",kc);
			lcd_Control_Write(0x80);						// Đưa con trỏ tới hàng 1 cột 1
			lcd_send_string("KHOANG CACH:");				// In
			lcd_Control_Write(0x8C);						// Đưa con trò tới hàng 1 cột 13
			lcd_send_string(distance);						// In
			Delay_ms(1000);									// Delay 1s
			USART_SendString(USART1,distance);				// Truyền UART xâu distance
			USART_SendString(USART1,"\n");					// Truyền UART kí tự xuống dòng		
	}
}

void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
void Delay_msST(uint16_t nTime)														// Hàm Delay tuyệt đối
{
		Time_ST = nTime;
	while(Time_ST !=0)
			{
			}
}
void I2C_LCD_Configuration(void)
{
    // Cấp xung clock cho ngoại vi và I2C
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);							// Sử dụng kênh I2C2 cua STM32
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Cấu hình chân SDA và SCL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;						// PB10 - SCL, PB11 - SDA
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								// Tần số 50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;		
    GPIO_Init(GPIOB, &GPIO_InitStructure);											// Khởi tạo GPIO PORTB			

    //Cấu hình I2C
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;										// Trạng thái I2C	
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;								// Độ rộng xung
    I2C_InitStructure.I2C_OwnAddress1 = 0; // 
    I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;									// Không cho phép nhận tín hiệu ACK return 
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;    	// địa chỉ I2C 7bit    
    I2C_InitStructure.I2C_ClockSpeed = 100000;										// Xung clock 10Mhz								
    I2C_Init(I2C2, &I2C_InitStructure);												// Khởi tạo I2C
    I2C_Cmd(I2C2, ENABLE);															// Cho phép bộ I2C hoạt động

}
