/**
 * @file Spi.cpp
 * @author huanghan0912 (huanghan0912@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 * 
 */
#include "Spi.h"

esp_err_t Spi::Init(const spi_host_device_t spi_peripheral, const int pin_miso, 
                    const int pin_mosi, const int pin_sclk,const spi_dma_chan_t SPI_DMA)
{
    esp_err_t status = ESP_OK;

    _spi_peripheral = spi_peripheral;
    _SPI_DMA = SPI_DMA;

    _spi_bus_cfg.mosi_io_num = pin_mosi;
    _spi_bus_cfg.miso_io_num = pin_miso;
    _spi_bus_cfg.sclk_io_num = pin_sclk;
    _spi_bus_cfg.quadwp_io_num = -1;
    _spi_bus_cfg.quadhd_io_num = -1;

    status |= spi_bus_initialize(spi_peripheral, &_spi_bus_cfg, _SPI_DMA);

    return status;
}

esp_err_t Spi::AddSlaveDevice(const uint8_t mode, const int ss,const uint8_t command_lengh,const uint8_t address_lengh, const int clock_speed_devider)
{
    esp_err_t status = ESP_OK;

    _spi_interface_cfg = {};
    _spi_interface_cfg.mode = mode;
     _spi_interface_cfg.clock_speed_hz = clock_speed_devider; // 80MHz/10 = 8MHz SPI speed
    _spi_interface_cfg.spics_io_num = ss;
    _spi_interface_cfg.queue_size = 7;
    _spi_interface_cfg.command_bits=command_lengh;
    _spi_interface_cfg.address_bits=address_lengh;

    status |= spi_bus_add_device(_spi_peripheral, &_spi_interface_cfg, &spi);

    return status;
}

esp_err_t Spi::WriteCmd(const uint8_t command){
     spi_transaction_t _spi_transaction;
     memset(&_spi_transaction, 0, sizeof(_spi_transaction));  
     _spi_transaction.length=8;
     _spi_transaction.tx_buffer=&command;
     _spi_transaction.user=(void*)0;
     return spi_device_polling_transmit(spi, &_spi_transaction);
}


esp_err_t Spi::WriteMultipleBytes( uint8_t* reg_data_buffer, const int byte_length, const uint8_t command)
{
     spi_transaction_t _spi_transaction;
     memset(&_spi_transaction, 0, sizeof(_spi_transaction));  
     _spi_transaction.length=8*byte_length;
     _spi_transaction.cmd=command;
     _spi_transaction.tx_buffer=reg_data_buffer;
     _spi_transaction.user=(void*)0;
     return spi_device_polling_transmit(spi, &_spi_transaction);
}

esp_err_t Spi::WriteMultipleBytes( uint16_t* reg_data_buffer, const int byte_length, const uint8_t command)
{
     spi_transaction_t _spi_transaction;
     memset(&_spi_transaction, 0, sizeof(_spi_transaction));  
     _spi_transaction.length=16*byte_length;
     _spi_transaction.cmd=command;
     _spi_transaction.tx_buffer=reg_data_buffer;
     _spi_transaction.user=(void*)0;
     return spi_device_polling_transmit(spi, &_spi_transaction);
}






