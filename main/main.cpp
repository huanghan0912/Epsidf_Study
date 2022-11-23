/**
 * @file main.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * 
 */

#include "Sd.h"
#include "Wifi.h"
#define DEBUG

Sd sd;

extern "C" void app_main(void) {
    //先初始化flash空间
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    
   sd.init();
   
}