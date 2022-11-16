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


static EventGroupHandle_t s_wifi_event_group;
void event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);

class Wifi
{
private:
    wifi_config_t wifi_config
    uint8_t Wifi_ssid[30];
    uint8_t Wifi_password[30];
public:
    //初始化wifi
    void init(char* ssid,char* password);
    //开启STA模式
    void STA_begin();
    //开始AP模式
    void AP_begin();
    //开启AP STA共存模式
    void STA_AP_begin();
    //
};





#endif
