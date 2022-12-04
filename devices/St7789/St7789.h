/**
 * @file St7789.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 * 
 */

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"
#include "Spi.h"
#include "string.h"
#include "esp_log.h"


#define PIN_NUM_MISO -1
#define PIN_NUM_MOSI GPIO_NUM_21
#define PIN_NUM_CLK  GPIO_NUM_20
#define PIN_NUM_CS   GPIO_NUM_39
#define PIN_NUM_RES  GPIO_NUM_36
#define PIN_NUM_DC   GPIO_NUM_38
#define PIN_NUM_BLK  GPIO_NUM_40

#define LCD_W 240
#define LCD_H 240

#define DMA_CHANNEL SPI_DMA_CH_AUTO
#define SPI_HOST SPI2_HOST


#define BLK_ON()    gpio_set_level(PIN_NUM_BLK,1);
#define BLK_OFF()   gpio_set_level(PIN_NUM_BLK,0);

#define LCD_SCL_SET() gpio_set_level(PIN_NUM_CLK,1);
#define LCD_SCL_CLR() gpio_set_level(PIN_NUM_CLK,0);
#define LCD_SDA_SET() gpio_set_level(PIN_NUM_MOSI,1);
#define LCD_SDA_CLR() gpio_set_level(PIN_NUM_MOSI,0);
#define LCD_CS_SET() gpio_set_level(PIN_NUM_CS,1);
#define LCD_CS_CLR() gpio_set_level(PIN_NUM_CS,0);
#define LCD_RES_SET() gpio_set_level(PIN_NUM_RES,1);
#define LCD_RES_CLR() gpio_set_level(PIN_NUM_RES,0);

#define LCD_DC_SET() gpio_set_level(PIN_NUM_DC,1);
#define LCD_DC_CLR() gpio_set_level(PIN_NUM_DC,0);

#define DELAY(X) vTaskDelay(((X)/ portTICK_PERIOD_MS))

class St7789 : public Spi
{
private:
    void LcdWriteCmd(const uint8_t cmd);
    void LcdWriteData(const uint8_t data);
    //发送16bit数据
    void LcdWriteData16(const uint16_t data);
public:
    void Init();
    //LCD清屏函数
    void clear();
    void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
    void LCD_Clear(uint16_t Color);
    void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color);	
};


