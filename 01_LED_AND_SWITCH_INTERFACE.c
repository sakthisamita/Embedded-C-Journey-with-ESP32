#include <stdio.h>  // For standard I/O
#include "driver/gpio.h"  // For connecting ESP usinf device driver
#include "freertos/FreeRTOS.h" // For API for performing tasks in ESP2
#include <portmacro.h> // For task delays

// Connect led to pin 2
// Connect the button to pin 5

#define led 2
#define button 5

void app_main (void)
{
    gpio_reset_pin (led);  // To reset the configuration of pin 2
    gpio_set_direction (led, GPIO_MODE_OUTPUT);  // Setting pin 2 as output
    
    gpio_reset_pin (button);  // To reset the configuration of pin 5
    gpio_set_pull_mode (button,GPIO_PULLUP_ONLY);  // Configure the button as pull up device
    gpio_set_direction (button, GPIO_MODE_INPUT);  // Configure pin 2 as input

    while (true) {
        int x = gpio_get_level (button);
        if (x==false) {
            gpio_set_level (led, true); // LED ON
        }
        else {
            gpio_set_level (led, false); // LED OFF
        }
        vTaskDelay (50 / portTICK_PERIOD_MS); 
    }
}
