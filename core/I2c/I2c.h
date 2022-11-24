/**
 * @file I2c.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * 
 */

#ifndef _I2C_H_
#define _I2C_H_

#include "driver/i2c.h"
#include "esp_intr_alloc.h"

class I2c
{
private:
        //从机地址
        uint8_t _slaveAddr;            //The slave address
        i2c_port_t _port;               //the I2C port number
        i2c_mode_t _mode;               //Select master or slave mode
        size_t _slv_rx_buf_len;         //Receive buffer length used in slave mode
        size_t _slv_tx_buf_len;         //Transmit buffer length used in slave mode
        int _intr_alloc_flags;          //Interrupt allocation, set to 0 in master mode,
public:
        // 初始化
        void Init(i2c_port_t port, size_t slv_rx_buf_len = 0, size_t slv_tx_buf_len = 0, int intr_alloc_flags = 0);
        ~I2c();
        //配置i2c的设置
        esp_err_t InitMaster(int sda_io_num,
                             int scl_io_num,
                             uint32_t clk_speed,
                             bool sda_pullup_en = false,
                             bool scl_pullup_en = false,
                             uint32_t clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL);
        void ResigerSlaveAddr(uint8_t dev_addr);
        uint8_t ReadByte(uint8_t dev_addr, uint8_t reg_addr);        
        esp_err_t WriteByte(uint8_t dev_addr, uint8_t reg_addr, uint8_t txData);
        esp_err_t ReadMultipleDatas(uint8_t dev_addr, uint8_t reg_addr, uint8_t *rx_data, int length);
        esp_err_t WriteMultipleDatas(uint8_t dev_addr, uint8_t reg_addr, uint8_t *tx_data, int length);
    
};





#endif