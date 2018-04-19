#include <stdio.h>
#include <unistd.h>
#include <Python.h>
#include "mraa.h"
#include "mraa/aio.h"

#define ANALOG_PIN 0
#define THRESHOLD 800

extern "C"
const char* return_string()
{
    mraa_aio_context adc;
    uint16_t value;
    mraa_result_t result;
    mraa_gpio_context gpio;
    adc = mraa_aio_init(ANALOG_PIN);
    if (adc == NULL){
        fprintf(stderr, "[-] Cannot init pin %d\n", ANALOG_PIN);
        return "cant initialize adc";
    }
    while (1)
        {
           value = mraa_aio_read(adc);
            if (value < THRESHOLD)
                return "board5, on";
            else
                return "board5, off";
            sleep(1);
        }
}
