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

static const char *TAG="St7789";

void St7789::LcdWriteCmd(const uint8_t cmd){
    LCD_DC_CLR();
    WriteCmd(cmd);
}

void St7789::LcdWriteData(const uint8_t data){
    LCD_DC_SET();
    WriteCmd(data);
}


void St7789::LcdWriteData16(const uint16_t data){
    LCD_DC_SET()
    WriteCmd((data>>8));
    WriteCmd(data);
}

void St7789::SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LcdWriteCmd(0x2a);//列地址设置
	LcdWriteData16(x1);
	LcdWriteData16(x2);
	LcdWriteCmd(0x2b);//行地址设置
	LcdWriteData16(y1);
	LcdWriteData16(y2);
	LcdWriteCmd(0x2c);//储存器写
}


void St7789::Clear(uint16_t Color)
{
	SetAddress(0,0,LCD_W-1,LCD_H-1);
	LCD_DC_SET();//写数据
	uint16_t color_temp[240*2];
	memset(color_temp, Color, sizeof(color_temp));
    for(uint16_t i=0;i<LCD_W/2;i++){
	 	WriteMultipleBytes(color_temp,240*2);
	}
}

IRAM_ATTR void St7789::Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color)	
{
	uint32_t size = (x2+1-x1)*(y2+1-y1)*2;
	SetAddress(x1,y1,x2,y2);
	LCD_DC_SET();//写数据
	uint32_t send_cnt 	= size/480;//需要整行刷新多少行
	uint32_t send_cnt2	= size%480;//整行刷不完还剩多少字节

	if(size==0)
	{
		printf("size=%u\r\n",size);
		return;
	}
	for(int i=0;i<send_cnt;i++){
		ESP_ERROR_CHECK(WriteMultipleBytes(&color[i*240],240));
	}
	if(send_cnt2!=0){
		ESP_ERROR_CHECK(WriteMultipleBytes(&color[send_cnt*240],send_cnt2));
	}
}



void St7789::Init(){


    ESP_ERROR_CHECK(Spi::Init(SPI_HOST,PIN_NUM_MISO,PIN_NUM_MOSI,PIN_NUM_CLK,DMA_CHANNEL));
    ESP_ERROR_CHECK(Spi::AddSlaveDevice(0,PIN_NUM_CS,0,0,SPI_MASTER_FREQ_80M));
    gpio_set_direction(PIN_NUM_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_RES, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_BLK, GPIO_MODE_OUTPUT);
    //Reset the display
    BLK_ON();
    LCD_RES_CLR();
	DELAY(100);
	LCD_RES_SET();
	DELAY(100);

    LcdWriteCmd(0x11); // Sleep out
	DELAY(120);
    LcdWriteCmd(0x13);
    

    LcdWriteCmd(0x36);
    LcdWriteData(0x00);

    // JLX240 display datasheet
    LcdWriteCmd(0xB6);
    LcdWriteData(0x0A);
    LcdWriteData(0x82);

    LcdWriteCmd(0xB0);
    LcdWriteData(0x00);
    LcdWriteData(0xE0); // 5 to 6 bit conversion: r0 = r5, b0 = b5

    LcdWriteCmd(0x3A);
    LcdWriteData(0x55);
    DELAY(10);

    //--------------------------------ST7789V Frame rate setting----------------------------------//
    LcdWriteCmd(0xB2);
    LcdWriteData(0x0c);
    LcdWriteData(0x0c);
    LcdWriteData(0x00);
    LcdWriteData(0x33);
    LcdWriteData(0x33);

    LcdWriteCmd(0xB7);      // Voltages: VGH / VGL
    LcdWriteData(0x35);

    //---------------------------------ST7789V Power setting--------------------------------------//
    LcdWriteCmd(0xBB);
    LcdWriteData(0x28);		// JLX240 display datasheet

    LcdWriteCmd(0xC0);
    LcdWriteData(0x0C);

    LcdWriteCmd(0xC2);
    LcdWriteData(0x01);
    LcdWriteData(0xFF);

    LcdWriteCmd(0xC3);       // voltage VRHS
    LcdWriteData(0x10);

    LcdWriteCmd(0xC4);
    LcdWriteData(0x20);

    LcdWriteCmd(0xC6);
    LcdWriteData(0x0f);

    LcdWriteCmd(0xD0);
    LcdWriteData(0xa4);
    LcdWriteData(0xa1);

    //--------------------------------ST7789V gamma setting---------------------------------------//
    LcdWriteCmd(0xE0);
    LcdWriteData(0xd0);
    LcdWriteData(0x00);
    LcdWriteData(0x02);
    LcdWriteData(0x07);
    LcdWriteData(0x0a);
    LcdWriteData(0x28);
    LcdWriteData(0x32);
    LcdWriteData(0x44);
    LcdWriteData(0x42);
    LcdWriteData(0x06);
    LcdWriteData(0x0e);
    LcdWriteData(0x12);
    LcdWriteData(0x14);
    LcdWriteData(0x17);

    LcdWriteCmd(0xE1);
    LcdWriteData(0xd0);
    LcdWriteData(0x00);
    LcdWriteData(0x02);
    LcdWriteData(0x07);
    LcdWriteData(0x0a);
    LcdWriteData(0x28);
    LcdWriteData(0x31);
    LcdWriteData(0x54);
    LcdWriteData(0x47);
    LcdWriteData(0x0e);
    LcdWriteData(0x1c);
    LcdWriteData(0x17);
    LcdWriteData(0x1b);
    LcdWriteData(0x1e);

    LcdWriteCmd(0x21);

    LcdWriteCmd(0x2A);    // Column address set
    LcdWriteData(0x00);
    LcdWriteData(0x00);
    LcdWriteData(0x00);
    LcdWriteData(0xEF);    // 239

    LcdWriteCmd(0x2B);    // Row address set
    LcdWriteData(0x00);
    LcdWriteData(0x00);
    LcdWriteData(0x01);
    LcdWriteData(0x3F);    // 319



    DELAY(120);
    LcdWriteCmd(0x29);
}

void St7789::SetOrientation(uint8_t orientation)
{
    // ESP_ASSERT(orientation < 4);

    const char *orientation_str[] = {
        "PORTRAIT", "PORTRAIT_INVERTED", "LANDSCAPE", "LANDSCAPE_INVERTED"
    };

    ESP_LOGI(TAG, "Display orientation: %s", orientation_str[orientation]);

    uint8_t data[] =
    {0xC0, 0x00, 0x60, 0xA0};
    ESP_LOGI(TAG, "0x36 command value: 0x%02X", data[orientation]);
    LcdWriteCmd(0x36);
    LcdWriteData(data[orientation]);
}