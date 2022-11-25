/**
 * @file Wifi.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * 
 */

#include "Wifi.h"



#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG_STA = "wifi_STA";
static const char *TAG_AP = "wifi_AP";
static const char *TAG_SCAN = "wifi_AP";

static int s_retry_num = 0;
uint16_t number = DEFAULT_SCAN_LIST_SIZE;			// 默认扫描列表大小


/**
 * @brief STA模式事件中断处理
 * 
 * @param arg 表示传递给handler函数的参数
 * @param event_base 事件基
 * @param event_id 表示事件ID
 * @param event_data 表示传递给这个事件的数据
 */
void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } 
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < ESP_MAXIMUM_RETRY) 
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG_STA, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG_STA,"connect to the AP fail");
    } 
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG_STA, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }




    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG_AP, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG_AP, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}


                                

/**
 * @brief 初始化wifi
 * 
 */
void Wifi::Init(){
   //创建默认事件组
    s_wifi_event_group = xEventGroupCreate();
    //初始化潜在的TCP/IP 栈
    ESP_ERROR_CHECK(esp_netif_init());
    //创建默认循环组
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    //初始化wifi驱动
    //必须先调用此 API，然后才能调用所有其他 WiFi API
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,//事件基，代表事件的大类
                                                        ESP_EVENT_ANY_ID,//事件ID,从ap中获取ip
                                                        &wifi_event_handler,
                                                        NULL,//表示需要传递给handler函数的参数
                                                        &instance_any_id));//类型为：esp_event_handler_instance_t指针
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        &instance_got_ip));

        
}





/**
 * @brief wifi的STA模式开启
 * 
 * @param ssid wifi广播
 * @param password wifi密码
 */
void Wifi::BeginSTA(char* ssid,char* password){

     //给_wifi_config中数据赋值
    strcpy((char *)_wifi_config.sta.ssid,ssid);
    strcpy((char *)_wifi_config.sta.password, password);
    
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &_wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG_STA, "wifi_init_sta finished.");

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);


    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG_STA, "connected to ap SSID:%s password:%s",
                  _wifi_config.sta.ssid,_wifi_config.sta.password);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG_STA, "Failed to connect to SSID:%s, password:%s",
                 _wifi_config.sta.ssid,_wifi_config.sta.password );
    } else {
        ESP_LOGE(TAG_STA, "UNEXPECTED EVENT");
    }

}



/**
 * @brief 开启wifi扫描
 * 
 */
void Wifi::Scan(){
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_start() );
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, _ap_info));// 获取搜索的具体AP信息
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&_ap_count));		//接入点的数量
    ESP_LOGI(TAG_STA, "Total APs scanned = %u", _ap_count);
    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < _ap_count); i++) {
		ESP_LOGI(TAG_STA, "SSID \t\t%s", _ap_info[i].ssid);		// 打印WIFI名称
		ESP_LOGI(TAG_STA, "RSSI \t\t%d", _ap_info[i].rssi);		// 打印信号强度	
		ESP_LOGI(TAG_STA, "Channel \t\t%d\n", _ap_info[i].primary);
	}
}


/**
 * @brief wifi的STA模式开启
 * 
 * @param ssid wifi广播
 * @param password wifi密码
 */
void Wifi::BeginAP(char* ssid,char* password){

    strcpy((char *)_wifi_config.ap.ssid,ssid);
    strcpy((char *)_wifi_config.ap.password, password);
    _wifi_config.ap.ssid_len = strlen(ssid);
    _wifi_config.ap.channel = CONFIG_ESP_WIFI_CHANNEL;
    _wifi_config.ap.max_connection = MAX_STA_CONNECT;
    _wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;

    //如果密码为空,则设置为开放模式                                                  
    if (strlen((char *)_wifi_config.ap.password) == 0) {
        _wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &_wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG_AP, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
            _wifi_config.ap.ssid,_wifi_config.ap.password,_wifi_config.ap.channel);
}