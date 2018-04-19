#include <stdio.h>
#include <unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>

#define DIGITAL_PIN 7
#define THRESHOLD 1

const char* return_string()
{
    mraa_aio_context adc;
    uint16_t value;
    mraa_result_t result;
    mraa_gpio_context gpio;

            /* Init Digital pin */
    gpio = mraa_gpio_init(DIGITAL_PIN);
    if (gpio == NULL) {
        fprintf(stderr, "[-] Initialisation of pin %d"\
                "failed. Is this pin exist on your platform?\n",
                DIGITAL_PIN);
        return "can't initialize output object";
    }
    printf("[+] Pin %d is initialised\n", DIGITAL_PIN);

    /* Set Digital pin direction */
    result = mraa_gpio_dir(gpio, MRAA_GPIO_IN);
    if (result != MRAA_SUCCESS) {
        mraa_result_print(result);
//        printf("[+] Pin %d is not initialised correctly\n", DIGITAL_PIN);
    } else {
  //      printf("[+] Pin %d is initialised as output\n", DIGITAL_PIN);
    }


    /* Infinite loop */
    while (1)
  {

            /* Capture the sound sensor value and send 1 or 0 */
           value = mraa_gpio_read(gpio);
                printf("value of detected sound is %d",value);            
              /* Light up if the value is 1 */
            if (value ==  THRESHOLD) {
               
                return "board1, on";
            } else {
                
                return "board1, off";
            }
            /* sleep for 0.1 second */
            sleep(1);
        }
}










