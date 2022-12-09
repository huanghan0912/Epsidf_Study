#include <stdio.h>
#include "St7789.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

St7789 st7789;

extern "C"  void app_main(void)
{
    st7789.Init();
    st7789.Clear(0x0000);
    uint16_t i = 0;
    while (1)
    {
        i++;
        st7789.Clear(i);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    
}