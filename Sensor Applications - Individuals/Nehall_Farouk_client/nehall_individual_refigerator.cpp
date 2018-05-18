        #include <stdio.h>

        #include <unistd.h>

        #include "mraa.h"

        #include "mraa/aio.h"

        

        /*  analog pin is the input */

        #define ANALOG_PIN  1


       /*  digital pin is the output */

        #define DIGITAL_PIN_LED  11

        #define DIGITAL_PIN_BUZZER 12

       /*   determining the THRESHOLD */

        #define THRESHOLD 41





       int main()
        {
	
          mraa_aio_context adc;

          uint16_t   value;

          mraa_result_t result1;

          mraa_result_t result2;

          mraa_gpio_context gpio1;

          mraa_gpio_context gpio2;





 /* Initialisation of Digital pin for LED */

        gpio1 = mraa_gpio_init(DIGITAL_PIN_LED);

        if (gpio1 == NULL)

         {

           printf(" Led pin  failed. check for pin %d \n", DIGITAL_PIN_LED);

         }

        printf("led Pin %d is initiated\n", DIGITAL_PIN_LED);



		

	

       /* Init Digital pin for BUZZER */

       gpio2 = mraa_gpio_init(DIGITAL_PIN_BUZZER);

       if (gpio2 == NULL)

        {

          printf("Buzzer  pin %d failed. check for pin %d \n", DIGITAL_PIN_BUZZER);

        }

       printf(" Buzzer Pin %d is initiated\n", DIGITAL_PIN_BUZZER);









        /* Initialisation of analog pin */

        adc = mraa_aio_init(ANALOG_PIN);

        if (adc == NULL)

         {

          printf(" pin %d is not initiated", ANALOG_PIN);

         }

        printf(" Pin %d is initiated\n", ANALOG_PIN);

		

		

	

       

        /* Set Digital pin direction For both LED and BUzzer */

        result1 = mraa_gpio_dir(gpio1, MRAA_GPIO_OUT);

        if (result1 != MRAA_SUCCESS)

         {

           mraa_result_print(result1);

           printf("	Led Pin  number %d is not initiated right\n", DIGITAL_PIN_LED);

         }

        else

         {

           printf("Led Pin %d is initiated as output\n", DIGITAL_PIN_LED);

         }



		 

		 

		result2 = mraa_gpio_dir(gpio2, MRAA_GPIO_OUT);

        if (result2 != MRAA_SUCCESS)

          {

             mraa_result_print(result2);

             printf("Buzzer Pin number %d is not initiated right\n", DIGITAL_PIN_BUZZER);

          }

        else

          {

             printf("Buzzer Pin %d is initiated as output\n", DIGITAL_PIN_BUZZER);

          }

	  

		  

        /* loop that read from sensor and make processing */



        while (12)

        {

		

        /* rea from the sensor  */

        value = mraa_aio_read(adc);

        printf("Pin A%d received %hu - ", ANALOG_PIN, value);



		

		

        /* light for low tempreture  and buzz for  tempreture higher than 18 */

		

        if (value < THRESHOLD)

          {

           mraa_gpio_write(gpio1, 1);

           printf("GPIO 1    tempreture %0.2f \n",float(value*0.47));

           mraa_gpio_write(gpio2 ,0);

          }



        else

          {

             mraa_gpio_write(gpio1, 0);

	     mraa_gpio_write(gpio2 ,1);

             printf("GPIO 0   tempreture %0.2f \n",float(value*0.47));

          }

		  

		  

        /* sleep for  0.1 second */

        sleep(1);

        }

    }


