# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# file(GLOB SRCS *.cpp)
# list(APPEND SOURCES "core/Sd/Sd.cpp")
# list(APPEND SOURCES "core/Wifi/Wifi.cpp")
# list(APPEND SOURCES "core/HttpServer/HttpServer.cpp")
# list(APPEND SOURCES "core/HttpClient/HttpClient.cpp")
# list(APPEND SOURCES "core/Spi/Spi.cpp")
# list(APPEND SOURCES "core/I2c/I2c.cpp")
# list(APPEND SOURCES "core/Uart/Uart.cpp")

set( SRCS
    core/Sd/Sd.cpp
    core/Wifi/Wifi.cpp
    core/HttpServer/HttpServer.cpp
    core/HttpClient/HttpClient.cpp
    core/Spi/Spi.cpp
    core/I2c/I2c.cpp
    core/Uart/Uart.cpp
 )


set(includedirs
    core/Sd/.
    core/Wifi/.
    core/HttpServer/.
    core/HttpClient/.
    core/Spi/.
    core/I2c/.
    core/Uart/.
    .
 )


 set(COMPONENT_REQUIRES
    esp_http_server
    esp_http_client
    fatfs
    )



idf_component_register(SRCS   "${SRCS}"
                    INCLUDE_DIRS "${includedirs} " 
                    PRIV_REQUIRES "${COMPONENT_REQUIRES}" )

