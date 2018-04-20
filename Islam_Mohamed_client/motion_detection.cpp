#include <stdio.h>
#include <unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>
#include <string>
#define ANALOG_PIN 0

#define THRESHOLD 800
extern "C"


const char* motion_detection()
{
    int DIGITAL_PIN= 7;
    mraa_aio_context adc;
    uint16_t value;
    mraa_result_t result;
    mraa_gpio_context gpio;

    /* Init analog pin */
    adc = mraa_aio_init(ANALOG_PIN);
    if (adc == NULL) {
        return "cant initialize adc";
    }

    gpio = mraa_gpio_init(DIGITAL_PIN);

    if (gpio == NULL)
    {
       return "can't initialize output object";
    }

    printf("[+] Pin %d is initialised\n", DIGITAL_PIN);

    result = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);

    if (result != MRAA_SUCCESS)
    {
        mraa_result_print(result);
    }
    else
    {
        printf("[+] Pin %d is initialised as output\n", DIGITAL_PIN);
    }

    while (1)
        {
           value = mraa_aio_read(adc);
           fprintf(stdout, "Pin A%d received %hu - ", ANALOG_PIN, value);

            if (value < THRESHOLD)
            {
                return "board7, off";
            }
            else
            {
                return "board7, on";
            }
        }
}
