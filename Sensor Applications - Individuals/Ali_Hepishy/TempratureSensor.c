#include<stdio.h>
#include<unistd.h>
#include "mraa.h"
#include "mraa/aio.h"
#include <Python.h>

/* Ali Hepishy Kamel Abdelhamid */

/*  analog pin is the input */
#define ANALOG_PIN  1
#define LED_PIN  4
#define BUZZER_PIN  5
#define THRESHOLD 25
/*  digital pin is the output */
#define Out_PIN_9 9
#define Out_PIN_10 10

/*
int main()
{
*/

extern "C"
const char* return_string()
{
	
mraa_aio_context temperature;
mraa_aio_context out_led;
mraa_aio_context out_buzz;
uint16_t value;
uint16_t counter;
mraa_result_t result;
mraa_gpio_context gpio1_led;
mraa_gpio_context gpio2_buzz;


temperature = mraa_aio_init(ANALOG_PIN);


if(temperature==NULL)
{
//return 1;
return "cant initialize temperature_Pin";
}

out_led  = mraa_aio_init(LED_PIN);

// Init input Digital pin for LED 
if(out_led ==NULL)
{

// return 1;
 return "can't initialize input LED";
}

out_buzz = mraa_aio_init(BUZZER_PIN);

// Init input Digital pin for Buzzer 
if(out_buzz==NULL)
{
printf("fail in pin %d\n",BUZZER_PIN);

//return 1;
 return "can't initialize input BUZZER";
}

/* Init output Digital pin for LED */

gpio1_led= mraa_gpio_init(Out_PIN_9);

if(gpio1_led==NULL)
{
printf("[-] fail in pin %d\n",Out_PIN_9);
// return -1;
 return "can't initialize output LED";
}

printf("[+] Pin %d is initialized\n", Out_PIN_9);


/* Init Digital pin for BUZZER */

gpio2_buzz= mraa_gpio_init(Out_PIN_10);

if(gpio2_buzz==NULL)
 {
	printf("[-] fail in pin %d\n",Out_PIN_10);
	// return -1;
  return "can't initialize output BUZZER";
 }

printf("[+] Pin %d is initialized\n", Out_PIN_10);


/* Set Digital pin direction */

result = mraa_gpio_dir(gpio1_led, MRAA_GPIO_OUT);

if (result != MRAA_SUCCESS)
 {
	mraa_result_print(result);
	printf("[-] Pin %d is not working correctly\n", Out_PIN_9);
 }
 else 
 {
	printf("[+] Pin %d is success as output\n", Out_PIN_9);
 }
 
result = mraa_gpio_dir(gpio2_buzz, MRAA_GPIO_OUT);

if (result != MRAA_SUCCESS)
 {
	mraa_result_print(result);
	printf("[-] Pin %d is not working correctly\n", Out_PIN_10);
 }
 else 
 {
	printf("[+] Pin %d is success as output\n", Out_PIN_10);
 }
 
 //initialize counter
 counter=0; 
  
while (1)
	{
	 // Capture the sensor value 
	value = mraa_aio_read(temperature);
	// to adjust output temperature to Celsius
	value= value * 0.48826125;
	
	if(value < THRESHOLD && mraa_aio_read(out_led ) > 0)
	{
		 mraa_gpio_write(gpio1_led, 0);
			 mraa_gpio_write(gpio2_buzz, 0);
		
			 counter=0;
			   return "board1, off";
	}
	if(value>=THRESHOLD)
		if(mraa_aio_read(out_led)==0)
		{
		 mraa_gpio_write(gpio1_led, 1);
		 counter+=1;
		}
		else
		{
		 counter += 1;
		 // raise alarm if temperature is greater than 25 continuously for 10 seconds 
		 if(counter >= 10)
		 {
			 		  
			 // raise alarm  
			 if(counter%2 == 0)
			  mraa_gpio_write(gpio2_buzz, 1);
			else 
				 mraa_gpio_write(gpio2_buzz, 0);
		  return "board1, on";
		 }
		}
	
	printf("Temperature is : %hu  received at PIN A%d  - Counter Now is: %hu\n",  value,ANALOG_PIN ,counter);
	
	// sleep for one second 
	sleep(1);
	}	
}




