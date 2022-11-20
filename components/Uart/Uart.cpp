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



// /**
//  * @brief 发送数据任务
//  * 
//  * @param  
//  */
//  void send_data_task(void *arg){
//     Uart* uart=(Uart*)arg;
//     static const char *TASK_TAG = "sendData_task";
//     //为给定标签设置日志级别。
//     esp_log_level_set(TASK_TAG, ESP_LOG_INFO);
//     while (1)
//     {
//         //TODO:发送数据设置
//         uart->send_data("test",TASK_TAG);
//         vTaskDelay(2000 / portTICK_PERIOD_MS);
//     }
//    vTaskDelete(NULL);
// }

/**
 * @brief 接收数据任务
 * 
 * @param arg 
 */
 void receive_data_task(void *arg){
    Uart* uart=(Uart*)arg;
    static const char *TASK_TAG = "receiveData_task";
    //为给定标签设置日志级别。
    esp_log_level_set(TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*) malloc(UART_BUF_SIZE+1);//分配一个内存块
    while (1) {
        const int rxBytes = uart_read_bytes(uart->get_uart_num(), data, UART_BUF_SIZE, 1000 / portTICK_RATE_MS);//返回数据的长度
        if (rxBytes > 0) {
            data[rxBytes] = 0;
            ESP_LOGI(TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            //将缓冲区转储到指定级别的日志。
            ESP_LOG_BUFFER_HEXDUMP(TASK_TAG, data, rxBytes, ESP_LOG_INFO);
        }
    }
    free(data);//释放内存块
    vTaskDelete(NULL);
}


/**
 * @brief 选择uart端口号
 * 
 * @param uart_num uart端口号{UART_NUM_0,UART_NUM_1.....}
 */
void Uart::init(uart_port_t uart_num){
    //判断该uart端口号是否使用,若则删除
    if (uart_is_driver_installed(uart_num)) {
		ESP_LOGI(TAG_Uart, "UART_NUM_%d already been uesd!",uart_num);
		uart_driver_delete(uart_num);
    }
    //配置uart
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
 * @param TAG 调试输出(方便调试)
 */
void Uart::send_data(const char *data,const char *TAG= "uart"){
    const int len = strlen(data);//计算数据长度
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    // ESP_LOGI("Write %d bytes", txBytes);
    ESP_LOGI(TAG, "Write %d bytes", txBytes);
}

/**
 * @brief 
 * 
 * @param uart 
 * @param Priority 
 */
void Uart::create_receive_task(void* uart,unsigned int Priority){
    xTaskCreate(receive_data_task, "uart_Rx_task", 1024*2,uart,Priority, NULL);
}


/**
 * @brief 清除uart
 * 
 */
void Uart::uart_delete(){
    uart_driver_delete(My_uart_num);
}

uart_port_t Uart::get_uart_num(){
    return My_uart_num;
}


