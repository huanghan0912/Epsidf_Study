/**
 * @file Uart.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-18
 * 
 * 
 */

#include "Uart.h"

const char *TAG_Uart = "uart";


/**
 * @brief 选择uart端口号
 * 
 * @param uart_num uart端口号
 */
void Uart::init(uart_port_t uart_num){
    if (uart_is_driver_installed(uart_num)) {
		ESP_LOGI(TAG_Uart, "UART_NUM_%d already been uesd!",uart_num);
		uart_driver_delete(uart_num);
    }
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
	ESP_ERROR_CHECK(uart_driver_install(uart_num, UART_BUF_SIZE , UART_BUF_SIZE , 0, NULL, 0));

    My_uart_num=uart_num;
}

/**
 * @brief 分配给 GPIO 引脚。
 * 
 * @param UART_TXD  TX 引脚 GPIO 编号。
 * @param UART_RXD  RX 引脚 GPIO 编号
 * @param UART_RTS  RTS 引脚 GPIO 编号
 * @param UART_CTS CTS 引脚 GPIO 编号
 */
void Uart::set_pin(int UART_TXD, int UART_RXD, int UART_RTS=-1, int UART_CTS=-1){
    ESP_ERROR_CHECK(uart_set_pin(My_uart_num,UART_TXD,UART_RXD,UART_RTS,UART_CTS));
}

/**
 * @brief 发送数据
 * 
 * @param data 数据内容
 */
void Uart::sendData(const char *data){
    const int len = strlen(data);//计算数据长度
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    // ESP_LOGI("Write %d bytes", txBytes);
    ESP_LOGI(TAG_Uart, "Write %d bytes", txBytes);
}

/**
 * @brief 清除uart
 * 
 */
void Uart::uart_delete(){
    uart_driver_delete(My_uart_num);
}