/**
 * @file St7789.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 * 
 */

#include "St7789.h"

typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes; //No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} lcd_init_cmd_t;

static lcd_init_cmd_t init_cmd[]{
    {0x36,{0xC0},1},
    {0x3A,{0x05},1},
    {0xB2,{0x0c,0x0c,0x00,0x33,0x33},5},
    {0xb7,{0x35},1},
    {0xbb,{0x19},1},
    {0xc0,{0x2c},1},
    {0xc2,{0x01},1},
    {0xc3,{0x12},1},
    {0xc4,{0x20},1},
    {0xc6,{0x0f},1},
    {0xd0,{0xa4,0xa1},2},
    {0xe0,{0xd0,0x04,0x0d,0x11,0x13,0x2b,0x3f,0x54,0x4c,0x18,0x0d,0x0b,0x1f,0x23},14},
    {0xe1,{0xd0,0x04,0x0c,0x11,0x13,0x2c,0x3f,0x44,0x51,0x2f,0x1f,0x1f,0x20,0x23},14}

};

void St7789::LcdWriteCmd(const uint8_t cmd){
    LCD_DC_CLR();
    WriteCmd(0,cmd);
}

void St7789::LcdWriteData(const uint8_t data){
    LCD_DC_SET();
    WriteCmd(0,data);
}


void St7789::LcdWriteData16(const uint16_t data){
    LCD_DC_SET()
    WriteCmd(0,(data>>8));
    WriteCmd(0,data);
}

void St7789::LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LcdWriteCmd(0x2a);//列地址设置
	LcdWriteData16(x1);
	LcdWriteData16(x2);
	LcdWriteCmd(0x2b);//行地址设置
	LcdWriteData16(y1+80);
	LcdWriteData16(y2+80);
	LcdWriteCmd(0x2c);//储存器写
}


void St7789::LCD_Clear(uint16_t Color)
{
	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
	LCD_DC_SET();//写数据
	uint16_t color_temp[240*2];
	memset(color_temp, Color, sizeof(color_temp));
    for(uint16_t i=0;i<LCD_W/2;i++){
	 	ESP_ERROR_CHECK(WriteRegisterMultipleBytes(0,color_temp,240*16*2,0));
	}
}

IRAM_ATTR void St7789::LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color)	
{
	uint32_t size = (x2+1-x1)*(y2+1-y1)*2;
	LCD_Address_Set(x1,y1,x2,y2);
	LCD_DC_SET();//写数据
	uint32_t send_cnt 	= size/480;//需要整行刷新多少行
	uint32_t send_cnt2	= size%480;//整行刷不完还剩多少字节

	if(size==0)
	{
		printf("size=%u\r\n",size);
		return;
	}
	for(int i=0;i<send_cnt;i++){
		ESP_ERROR_CHECK(WriteRegisterMultipleBytes(0,&color[i*240],240*16,0));
	}
	if(send_cnt2!=0){
		ESP_ERROR_CHECK(WriteRegisterMultipleBytes(0,&color[send_cnt*240],send_cnt2*8,0));
	}
}



void St7789::Init(){


    ESP_ERROR_CHECK(Spi::Init(SPI_HOST,PIN_NUM_MISO,PIN_NUM_MOSI,PIN_NUM_CLK,DMA_CHANNEL));
    ESP_LOGI("1","1");
    ESP_ERROR_CHECK(Spi::RegisterDevice(3,PIN_NUM_CS,0,0,SPI_MASTER_FREQ_10M));
    ESP_LOGI("1","2");
    gpio_set_direction(PIN_NUM_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_RES, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_BLK, GPIO_MODE_OUTPUT);
    //Reset the display
    LCD_RES_CLR();
	DELAY(100);
	LCD_RES_SET();
	DELAY(100);

    LcdWriteCmd(0x11); 
    ESP_LOGI("1","3");
	DELAY(120);
    for(int i=0;i<13;i++){
        ESP_ERROR_CHECK(WriteRegisterMultipleBytes(0,init_cmd[i].data,init_cmd[i].databytes,init_cmd[i].cmd));
    }
    LcdWriteCmd(0x21); 
    LcdWriteCmd(0x11); 
    LcdWriteCmd(0x29); 


}