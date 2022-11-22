/**
 * @file Http.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-21
 * 
 * 
 */
#ifndef _HTTP_H_
#define _HTTP_H_

#include "esp_http_server.h"
#include "esp_log.h"


esp_err_t Http_handler(httpd_req_t *req);

class Http
{
private:
     httpd_config_t config;
     httpd_handle_t server= NULL;
     httpd_uri_t test_uri = {
        .uri      = "/",
        .method   = HTTP_GET,
        .handler  = Http_handler,
        .user_ctx = NULL
    };
public:
    httpd_handle_t  init();
    
};






#endif