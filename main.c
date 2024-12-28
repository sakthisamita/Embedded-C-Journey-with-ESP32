#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

// Connect led to pin 2
#define led 2

void app_main (void)
{
    gpio_reset_pin (led);
    gpio_set_direction (led, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level (led, true); // LED ON
        vTaskDelay (1000 / portTICK_PERIOD_MS); 
        gpio_set_level (led, false); // LED OFF
        vTaskDelay (1000 / portTICK_PERIOD_MS); 
    }
}