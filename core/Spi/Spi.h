/**
 * @file Spi.h
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 * 
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "../../user_config.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"




class Spi
{
private:
    //configuration structure for a SPI bus.
    spi_bus_config_t _spi_bus_cfg;
    spi_device_interface_config_t _spi_interface_cfg;
    spi_device_handle_t _handle={};
    //the num of three SPI peripherals that are software-accessible in it.
    spi_host_device_t _spi_peripheral;       
    spi_transaction_t _spi_transaction; 
    spi_dma_chan_t _SPI_DMA;



public:
    //初始化
    esp_err_t Init(const spi_host_device_t spi_peripheral, const int pin_miso, const int pin_mosi, const int pin_sclk,const spi_dma_chan_t SPI_DMA=0);
    esp_err_t TransferByte(const uint8_t reg_addr, const uint8_t data, const uint8_t command = 0);

    esp_err_t TransferMultiplesBytes(const uint8_t reg_addr, uint8_t* tx_buf, uint8_t* rx_buf, size_t command_length, const uint8_t command = 0);
    esp_err_t TransferMultiplesBytes(const uint8_t reg_addr, uint16_t* tx_buf, uint16_t* rx_buf, size_t command_length, const uint8_t command = 0);

    esp_err_t RegisterDevice(const uint8_t mode, const int ss, const int addr_length, const int command_length, const int clock_speed_devider = SPI_MASTER_FREQ_20M);
    uint8_t ReadRegister(const uint8_t reg_addr, const uint8_t command = 0);
    void WriteCmd(const uint8_t reg_addr, const uint8_t command);
    esp_err_t WriteRegister(const uint8_t reg_addr, const uint8_t reg_data, const uint8_t command = 0);
    esp_err_t WriteRegisterMultipleBytes(const uint8_t reg_addr, uint8_t* reg_data_buffer, const int byte_length, const uint8_t command = 0);
    esp_err_t WriteRegisterMultipleBytes(const uint8_t reg_addr, uint16_t* reg_data_buffer, const int byte_length, const uint8_t command = 0);
    esp_err_t ReadRegisterMultipleBytes(const uint8_t reg_addr, uint8_t* reg_data_buffer, const int byte_length, const uint8_t command = 0);
    spi_device_handle_t GetHandle(void);
    
};





#endif