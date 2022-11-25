#include "HttpServer.h"


static const char *TAG_HTTP="Http" ;

httpd_handle_t HttpServer::Init(){
    config = HTTPD_DEFAULT_CONFIG();
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_ERROR_CHECK(httpd_register_uri_handler(server,&test_uri));
    }
    else ESP_LOGI(TAG_HTTP, "fail to httpd_start");
    return server;
}

esp_err_t HttpHandler(httpd_req_t *req)
{
    const char resp[] = "<h1>Hello World</h1>";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}