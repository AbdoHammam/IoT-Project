#include <iostream>
#include <unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>
#include <string>

using namespace std;

#define ANALOG_PIN 0
#define THRESHOLD 500

extern "C"


const char* return_light_status()
{
    mraa_aio_context adc;
    uint16_t value;

    adc = mraa_aio_init(ANALOG_PIN);
    if (adc == NULL)
    {
        return "cant initialize adc";
    }

    while (true)
    {
        value = mraa_aio_read(adc);
        cout << "Pin "<<to_string(ANALOG_PIN) << " received " <<to_string(value) << endl;

        if (value > THRESHOLD)
        {
            return "board1, on";
        }
        else
        {
            return "board1, off";
        }
    }
}
