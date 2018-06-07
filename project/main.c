#include "stm32f10x.h"
#include "i2c_lcd.h" 
#include "main.h"
int kc;
char distance[5];
uint32_t Time_ST=0;							// bien delay bang system tick timer	

GPIO_InitTypeDef 					GPIO_InitStructure;
I2C_InitTypeDef						I2C_InitStructure;       // khai bao bien de su dung thu vien chuan I2C cua ST.

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void Delay_msST(uint16_t nTime);              // ham delay tuyet doi bang system tick timer
void I2C_LCD_Configuration(void);              // chuong trinh con cau hinh I2C
void cauhinhTIMER() {    														// ts 72mhz, chia trc 72=> 1tr xung = 1s => 1xung = 1us     
	TIM_TimeBaseInitTypeDef   TM;        
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM4, ENABLE );     
	TM.TIM_ClockDivision =0;         									// Không chia xung   
	TM.TIM_CounterMode = TIM_CounterMode_Up ;         // dem lên  
	TM.TIM_Period = 9999;         										// Giá tri tu dong nap lai là 9 999        
	TM.TIM_Prescaler = 71;         										// bo chia truoc 72        
	TM.TIM_RepetitionCounter =0;         							// bao ngat khi tran        
	TIM_TimeBaseInit (TIM4,&TM);        
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );        
	TIM_Cmd(TIM4,ENABLE ); } 

int main(void)
{
x	SysTick_Config(SystemCoreClock/1000);
	GPIO_Configuration();
	I2C_LCD_Configuration();
	lcd_init ();   
	SystemInit();
	delay_init(72);
	cauhinhTIMER();
	// ham khoi dong LCD16x2
	USART1_Configuration();

  while (1)
  {
		//lcd_init (); 
		
		GPIO_WriteBit(GPIOB,HCSR04_TRIGGER_PIN,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,HCSR04_TRIGGER_PIN)));
		Delay_ms(100);
		kc = HCSR04_Read();
		if (kc < 10)
			sprintf(distance,"%d  ",kc);
		else if (kc < 100)
			sprintf(distance,"%d ",kc);
		else 
			sprintf(distance,"%d",kc);
		lcd_Control_Write(0x80);
		lcd_send_string("KHOANG CACH:");
		lcd_Control_Write(0x8C);
		lcd_send_string(distance);
		Delay_ms(1000);
		USART_SendString(USART1,"\n");
		USART_SendString(USART1,distance);
		
  }
}

void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
void Delay_msST(uint16_t nTime)																			// ham delay tuyet doi
{
		Time_ST = nTime;
	while(Time_ST !=0)
			{
			}
}
void I2C_LCD_Configuration(void)
{
    // cap clock cho ngoai vi va I2C
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);							// su dung kenh I2C2 cua STM32
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // cau hinh chan SDA va SCL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;						//PB10 - SCL, PB11 - SDA
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // cau hinh I2C
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0; // 
    I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;       
    I2C_InitStructure.I2C_ClockSpeed = 100000;										
    I2C_Init(I2C2, &I2C_InitStructure);
    // cho phep bo I2C hoat dong
    I2C_Cmd(I2C2, ENABLE);

}
