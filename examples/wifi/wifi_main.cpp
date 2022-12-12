/**
 * @file wifi_main.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * 
 */

#include "Wifi.h"
#define DEBUG


//使用的组件
Wifi wifi;



extern "C" void app_main(void) {
    //先初始化flash空间
     esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    
    wifi.Init();
    wifi.AP_begin("12","12345678");
    wifi.STA_begin("H-H","2235812260");
    wifi.scan();
   
}