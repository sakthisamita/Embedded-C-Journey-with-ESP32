#include <stdio.h>  // For standard I/O
#include "driver/gpio.h"  // For connecting ESP using device driver
#include "freertos/FreeRTOS.h" // For API for performing tasks in ESP2
#include "esp_log.h"  // For debugging
#include "inttypes.h"  // For using datatypes
#include <portmacro.h> // For task delays

// Connect the button to pin 5
#define interrupt_pin 5

uint16_t count=0;
bool button=false;

// IRAM_ATTR ensures ISR code is stored in internal RAm for faster exexution
static void IRAM_ATTR gpio_isr_handle (void *arg) 
{
    count++;
    button=true;

    gpio_isr_handler_add (interrupt_pin, gpio_isr_handle, NULL);  // Adds the ISR gpio_isr_handle to handle interrupts on the interrupt_pin
    gpio_intr_enable (interrupt_pin);  // Enable interrupts for pin 5
}

void app_main (void)
{
    gpio_reset_pin (interrupt_pin);  // To reset the configuration of pin 5
    gpio_set_direction (interrupt_pin, GPIO_MODE_INPUT);  // Configure pin 5 as input
    gpio_set_pull_mode (interrupt_pin, GPIO_PULLUP_ONLY);  // Configure interrupt_pin as pull up
    gpio_set_intr_type (interrupt_pin, GPIO_INTR_POSEDGE);  // Configures GPIO interrupt to positive edge (Button ON)

    gpio_install_isr_service(0);  // Install ISR
    gpio_isr_handler_add (interrupt_pin, gpio_isr_handle, NULL);  // Add ISR handler 
    gpio_intr_enable (interrupt_pin);  // Enable interrupts for pin 5

    while (true) {
        if (button==true) {
            printf ("%d\n", count);
            button=false;
        }
        vTaskDelay (100 / portTICK_PERIOD_MS);
    }
}