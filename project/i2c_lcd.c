#include "i2c_lcd.h"

// Hàm truyền dữ liệu
void lcd_Write_byte(char data)
{
    /* Tạo tín hiệu START*/
    I2C_GenerateSTART(I2C_Chanel, ENABLE);
    /* Kiểm tra EV5 và cài đặt mode master */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_MODE_SELECT));
    /* Gửi địa chỉ PCF8574A*/
    I2C_Send7bitAddress(I2C_Chanel, PCF8574A_Address, I2C_Direction_Transmitter);
	/* Kiểm tra EV6 */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Gửi data*/
    I2C_SendData(I2C_Chanel, data);
    /* Kiểm tra EV8 */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Tạo tín hiệu STOP*/
    I2C_GenerateSTOP(I2C_Chanel, ENABLE);		
}

// Hàm khởi tạo LCD
void lcd_init (void)
{
	/* Set 4-bits interface */
	lcd_Control_Write(0x33);		 
	Delay_msST(10);
	lcd_Control_Write(0x32);
	Delay_msST(50);
	/*Thiết lập LCD giao tiếp 4bit, hiển thị hàng 1 */
	lcd_Control_Write(0x28);
		Delay_msST(50);	
	/* Xóa LCD */
	lcd_Control_Write(0x01);
		Delay_msST(50);
	/*Chờ 50ms */
	
	/* set entry mode */
	lcd_Control_Write(0x06);	Delay_msST(50);;
	/* Hiển thị màn hình, nhấp nháy con trỏ */	
	lcd_Control_Write(0x0C);	Delay_msST(50);;
	/* Trả bộ đếm địa chỉ về 0 */
	lcd_Control_Write(0x02);	Delay_msST(50);
}

// Hàm ghi dữ liệu
void lcd_Data_Write(char data){
	char data_u, data_l;
	uint8_t data_t[4],i=0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x0d;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0d;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	for(i = 0;i<4;i++)
	{
	     lcd_Write_byte(data_t[i]);
	}
}

// Hàm ghi lệnh LCD
void lcd_Control_Write(char data){
    char data_u, data_l;
	uint8_t data_t[4],i=0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x04; 	//en=1, rs=0
	data_t[1] = data_u;  		//en=0, rs=0
	data_t[2] = data_l|0x04;  	//en=1, rs=0
	data_t[3] = data_l|0x08;  	//en=0, rs=0
	for(i = 0;i<4;i++)
	{
	     lcd_Write_byte(data_t[i]);
	}

}

// Hàm gửi chuỗi lên LCD
void lcd_send_string (char *str){
	while (*str) lcd_Data_Write (*str++);
}

// Hàm xóa LCD
void Delete_LCD(void){
	lcd_Control_Write(0x01);
	Delay_msST(10);
}
