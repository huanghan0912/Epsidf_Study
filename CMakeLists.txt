# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)



set( SRCS_CORE
    core/Sd/Sd.cpp
    core/Wifi/Wifi.cpp
    core/HttpServer/HttpServer.cpp
    core/HttpClient/HttpClient.cpp
    core/Spi/Spi.cpp
    core/I2c/I2c.cpp
    core/Uart/Uart.cpp
 )

set( SRCS_DEVICES
    devices/St7789/St7789.cpp
)



set(INCLUDE_CORE
    core/Sd
    core/Wifi
    core/HttpServer
    core/HttpClient
    core/Spi
    core/I2c
    core/Uart
)
 set(INCLUDE_DEVICES
    devices/St7789
 )



 set(COMPONENT_REQUIRES
    esp_http_server
    esp_http_client
    fatfs
    nvs_flash 
    esp_event 
    esp_wifi
    )



idf_component_register(SRCS   "${SRCS_CORE}" "${SRCS_DEVICES}"
                    INCLUDE_DIRS "${INCLUDE_CORE}" "${INCLUDE_DEVICES}" 
                    PRIV_REQUIRES "${COMPONENT_REQUIRES}" )

