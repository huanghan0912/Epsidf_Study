/**
 * @file HttpClient.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * 
 */
#ifndef _HTTPCLIENT_H_
#define _HTTPCLIENT_H_
#include "esp_http_client.h"

class HttpClient
{
private:
    esp_http_client_config_t client_config;
public:
     esp_http_client_handle_t client;

    //不同参数的初始化
    void Init();       //默认
    void Init(char* url);   //默认get调用api

};






#endif
