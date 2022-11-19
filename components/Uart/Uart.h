/**
 * @file Uart.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * 
 */

#ifndef _UART_H_
#define _UART_H_

#include "user_config.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "string.h"
#include "esp_log.h"




#define UART_BUF_SIZE		1024





class Uart
{
private:
    //uart端口号
    uart_port_t My_uart_num;
    //uart配置信息
   uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

public:
    //选择uart端口号
    void init(uart_port_t uart_num);
    //设置uart的引脚
    void set_pin(int UART_TXD, int UART_RXD, int UART_RTS, int UART_CTS);
    //发送数据
    void sendData(const char *data,const char *TAG);
    
    
    //清除uart
    void uart_delete();



    //
    uart_port_t get_uart_num();
};

 //发送数据任务
static void sendData_task(void *arg);
//接收数据任务
static void receiveData_task(void *arg);


#endif