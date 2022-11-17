/**
 * @file Wifi.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * 
 */
#ifndef _WIFI_H_
#define _WIFI_H_

#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"


/*******************************************个人配置*************************************************/

//esp连接最大等待事件
#define ESP_MAXIMUM_RETRY  1000
//AP模式最大可连接量
#define MAX_STA_CONNECT 5
//AP模式信道
#define CONFIG_ESP_WIFI_CHANNEL 12

static EventGroupHandle_t s_wifi_event_group;
//STA模式事件中断处理
void STA_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);
//ap模式事件中断处理
void AP_wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);

class Wifi
{
private:
    wifi_config_t wifi_config;
    uint8_t Wifi_ssid[30];
    uint8_t Wifi_password[30];
public:
    //初始化wifi的STA模式
    void STA_init(char* ssid,char* password);
    //初始化wifi的AP模式
    void AP_init(char* Your_ssid,char* Your_password);
    //开启STA模式
    void STA_begin();
    //wifi开始寻找附近wifi
    void scan();
    //开始AP模式
    void AP_begin();
    //开启AP STA共存模式
    void STA_AP_begin();
    //
};





#endif
