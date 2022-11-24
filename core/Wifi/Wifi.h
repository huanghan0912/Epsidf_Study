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


#include "../../user_config.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"


/*******************************************个人配置*************************************************/

//esp连接最大等待时间
#define ESP_MAXIMUM_RETRY  USER_ESP_MAXIMUM_RETRY
//AP模式最大可连接量
#define MAX_STA_CONNECT USER_MAX_STA_CONNECT
//AP模式信道
#define CONFIG_ESP_WIFI_CHANNEL USER_CONFIG_ESP_WIFI_CHANNEL
//扫描ap的最大数量
#define DEFAULT_SCAN_LIST_SIZE USER_DEFAULT_SCAN_LIST_SIZE

/*******************************************全局变量*****************************************************/
static EventGroupHandle_t s_wifi_event_group;

/*******************************************函数********************************************************/
//STA模式事件中断处理
void STA_wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);
//ap模式事件中断处理
void AP_wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);
//扫描模式中断处理
void Scan_wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);



/*******************************************类*********************************************************/
class Wifi
{
private:
    //扫描出ap,和其数目
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;	
    //wifi配置
    wifi_config_t wifi_config;
    //wifi名称和密码
    uint8_t Wifi_ssid[30];
    uint8_t Wifi_password[30];
public:
    //初始化wifi
    void init();
    //开始STA模式
    void STA_begin(char* ssid,char* password);
    //wifi开始寻找附近wifi
    void scan();
    //开始AP模式
    void AP_begin(char* Your_ssid,char* Your_password);
    //TODO:开启AP STA共存模式
    void STA_AP_begin();
    //
};





#endif
