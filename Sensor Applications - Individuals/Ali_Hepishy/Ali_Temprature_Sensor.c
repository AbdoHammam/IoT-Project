#include<stdio.h>
#include<unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>
/* Ali Hepishy Kamel Abdelhamid */
/*  analog pin is the input */
#define ANALOG_PIN  0
#define THRESHOLD 50
/*  digital pin is the output */
#define Out_PIN 11


extern "C"
const char* return_string()
{
        mraa_aio_context temperature;
        mraa_aio_context out_led;
        uint16_t value=0;
		uint16_t counter=0;
        mraa_result_t result;
        mraa_gpio_context gpio1_led;
        temperature = mraa_aio_init(ANALOG_PIN);
        if(temperature==NULL)
        {
                return "cant initialize temperature_Pin";
        }
        /* Init output Digital pin for LED */
        gpio1_led= mraa_gpio_init(Out_PIN);
        if(gpio1_led==NULL)
        {
                printf("[-] fail in pin %d\n",Out_PIN);
                return "can't initialize output LED";
        }
      printf("[+] Pin %d is initialized\n", Out_PIN);
        /* Set Digital pin direction */
        result = mraa_gpio_dir(gpio1_led, MRAA_GPIO_OUT);
        if (result != MRAA_SUCCESS)
        {
                mraa_result_print(result);
                printf("[-] Pin %d is not working correctly\n", Out_PIN);
        }
        while (1)
                {
                        value = mraa_aio_read(temperature);                         // Capture the sensor value
                        value= value * 0.48826125;									// to adjust output temperature to Celsius
						printf("Temperature is : %hu  received at PIN A%d  - Counter Now is: %hu\n",value,ANALOG_PIN,counter);
					   if(value < THRESHOLD)
                        {
                                        mraa_gpio_write(gpio1_led, 0);
                                        counter=0;
                                        return "board8,off";
                        }
                        if(value>=THRESHOLD)
                        {
                                mraa_gpio_write(gpio1_led, 1);
                                counter+=1;
                                // raise alarm if temperature is greater than Threshold continuously for 10 seconds
                                if(counter >= 10)
                                        {
                                                return "board8,on";
                                        }
                        }                      
                        sleep(1);                         // sleep for one second
                }
}