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
        int _port;
public: 
        esp_err_t Init(i2c_port_t port, size_t I2C_SDA , size_t I2C_SCL , int i2c_master_freqhz );
        void DeInit(i2c_port_t port); 
        uint8_t ReadByte(uint8_t dev_addr, uint8_t reg_addr);        
        esp_err_t WriteByte(uint8_t dev_addr, uint8_t reg_addr, uint8_t txData);
        esp_err_t ReadMultipleDatas(uint8_t dev_addr, uint8_t reg_addr, uint8_t *rx_data, int length);
        esp_err_t WriteMultipleDatas(uint8_t dev_addr, uint8_t reg_addr, uint8_t *tx_data, int length);
    
};





#endif