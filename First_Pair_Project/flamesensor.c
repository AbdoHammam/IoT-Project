#include <stdio.h>
#include <unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>

#define ANALOG_PIN 0
#define THRESHOLD 600

extern "C"
const char* return_string()
{
    mraa_aio_context adc;
    uint16_t value;
    mraa_result_t result;
    mraa_gpio_context gpio;
 
    /* Init analog pin */
    adc = mraa_aio_init(ANALOG_PIN);
    if (adc == NULL) {
        fprintf(stderr, "[-] Cannot init pin %d\n", ANALOG_PIN);
        return "cant initialize adc";
    }
 
 
 
    /* Infinite loop */
    while (1)
        {
 
            /* Capture the sensor value */
           value = mraa_aio_read(adc);
	printf("%d\n",value);
            /* Light up if the value is higher */
            if (value < THRESHOLD) {
                //result = mraa_gpio_write(gpio, 0);
		
                return "board8, on";
            } else {
                //result = mraa_gpio_write(gpio, 1);
                return "board8, off";
            }
            /* sleep for 0.1 second */
            sleep(1);
        }
}
