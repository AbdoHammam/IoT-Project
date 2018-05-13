#include <stdio.h>
#include <unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>
#define ANALOG_PIN 2
#define DIGITAL_PIN 7
#define THRESHOLD 40

const char* my_string()
{
        mraa_aio_context adc;
        float value;
        mraa_result_t result;
       /* mraa_gpio_context gpio;*/
        float sensor_voltage;
        float celsius_temp;

        /* Init analog pin */
        adc = mraa_aio_init(ANALOG_PIN);
        if (adc == NULL) {
        printf("[-] Cannot init pin %d\n", ANALOG_PIN);
        return "Error 1";
        }


        /* Init Digital pin */
        /*gpio = mraa_gpio_init(DIGITAL_PIN);
        if (gpio == NULL)
        printf("[-] Initialisation of pin %d"\
        "failed. Is this pin exist on your platform?\n",
        DIGITAL_PIN);
        return "Error -1";
        }
        printf("[+] Pin %d is initialised\n", DIGITAL_PIN);*/
        /* Set Digital pin direction */
        /*result = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
        if (result != MRAA_SUCCESS) {
        mraa_result_print(result);
        printf("[+] Pin %d is not initialised correctly\n", DIGITAL_PIN);
        } else {
        printf("[+] Pin %d is initialised as output\n", DIGITAL_PIN);  }
                                                        */
 /* Infinite loop */
        while (1)
        {
                sleep(1);
                int avg_reading=0;
                int i=0;
                for(i=0;i<124;i++)
                {
                        /* Capture the sensor value */
                        value = mraa_aio_read(adc);
                        avg_reading+=value;
                }
                avg_reading=avg_reading/124;
                value=avg_reading;
                printf("Pin A%d received %.0f - ", ANALOG_PIN, value);
                /* Light up if the value is higher */
                sensor_voltage= (value/1024.0)*5.0;
                /* printf("sensor_voltage: %.2f ",sensor_voltage);*/
                celsius_temp=sensor_voltage*100.0;

                printf("Degrees in Celsius: %.2f ",celsius_temp);
                if (celsius_temp > THRESHOLD) {
                        /* result = mraa_gpio_write(gpio, 1);*/
                        return "board3, on";
                        printf("GPIO 1\n");

                } else { /* Shut down if lower */
                        /*result = mraa_gpio_write(gpio, 0);*/
                        printf("GPIO 0\n");
                        return "board3, off";
                }
                /* sleep for 0.1 second */
        }
}
