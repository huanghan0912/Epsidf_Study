/**
 * @file HttpClient.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * 
 */
#include "HttpClient.h"
#include "string.h"
#include "ESP_LOG.h"


static const char *TAG_HTTP="HttpClient";
/**
 * @brief 默认初始化
 * 
 */
void HttpClient::Init(){
    client = esp_http_client_init(&client_config);
    ESP_LOGI(TAG_HTTP,"init finished");
}
/**
 * @brief 用于常见获取网络的初始化,默认为get方法
 * 
 * @param url 调用api的url
 */
void HttpClient::Init(char* url){
    client_config.url=url;
    client = esp_http_client_init(&client_config);
    //Set http request method
    esp_http_client_set_method(client, HTTP_METHOD_GET);
    ESP_LOGI(TAG_HTTP,"init finished");
}