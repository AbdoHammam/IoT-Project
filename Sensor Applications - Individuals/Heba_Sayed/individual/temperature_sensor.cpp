#include "mraa.h"
#include <stdio.h>
#include <unistd.h>
#include<time.h>


#define DIGITAL_PIN 5

uint getByte(int b,int buf[]){
 int i;
 uint result=0;
 b=(b-1)*8+1;
 for(i=b;i<=b+7;i++){
  result<<=1;
  result |= buf[i];
 }
 return result;
}


void wait(int seconds){
	clock_t endwait;
	endwait=clock()+seconds*CLOCKS_PER_SEC;
	while (clock()<endwait);
}

int main()
{
 const struct sched_param priority={1};
 sched_setscheduler(0,SCHED_FIFO,&priority);
 int buf[41];
 mraa_result_t result;
 mraa_gpio_context pin = mraa_gpio_init(3);
 mraa_gpio_context gpio;
 gpio = mraa_gpio_init(DIGITAL_PIN);
 
 result = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
 
 
 while(1)
 {
	 
	 
	 mraa_gpio_use_mmaped(pin,1);
	 mraa_gpio_dir(pin, MRAA_GPIO_OUT_HIGH);
	 
	 mraa_gpio_write(pin, 0);
	 usleep(1000);
	 mraa_gpio_dir(pin, MRAA_GPIO_IN);

	 int i, j;
	 for(j=0;j<41;j++){
	  for(i=1;i<200;i++){
	   if(mraa_gpio_read(pin)==1)break;
	  };
	  for(i=1;i<200;i++){
	   if(mraa_gpio_read(pin)==0)break;
	  }
	  buf[j]=0;
	  if(i>75)buf[j]=1;
	 }


	 int byte1=getByte(1,buf);
	 int byte2=getByte(2,buf);
	 int byte3=getByte(3,buf);
	 int byte4=getByte(4,buf);
	 int byte5=getByte(5,buf);

	 printf("Checksum %d %d \n",byte5,
		 (byte1+byte2+byte3+byte4) & 0xFF);
		int Checksum = (byte1+byte2+byte3+byte4) & 0xFF;
	 float temperature;
	 int neg=byte3&0x80;
	 byte3=byte3&0x7F;
	 temperature= (float) (byte3<<8 |byte4)/10.0;
	 if(neg>0)temperature=-temperature;
	 if(Checksum == byte5)
	 {
		printf("Temperature= %f \n",temperature);
		result = mraa_gpio_write(gpio, 1);
		wait(5);
		result = mraa_gpio_write(gpio, 0);
		break;
	 }
	 else
	 {
		 printf("transmission of data failed Temperature= %0.f \n",temperature);
		 result = mraa_gpio_write(gpio, 0);
	 }
	 wait(5);
 }

 return MRAA_SUCCESS;
}

