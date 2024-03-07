//main.c
#include<LPC21xx.h>
#include <stdio.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "lcd.h"
#include "adc.h"
#include "adc_defines.h"
#include "lm35.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "uart0.h"
#include "esp01.h"

#define GAS  20

u32 Temp,Smoke;
char LM35[10],MQ_2[2];

extern char buff[200];
extern unsigned char i;


int main()
{
    s32 c=0,min_dummy;

  	PREINT=PREINT_VAL;
  	PREFRAC=PREFRAC_VAL;

  	rtc_init(); //initialize all seconds,minute and hour values
  	CCR=0x01; //timer started

	//min_dummy=MIN;

	LCD_Init();
	Init_ADC();
	InitUART0();

	Write_str_LCD("Welcome To IoT");
	Write_CMD_LCD(0xC0);
	Write_str_LCD("   Project   ");
	delay_ms(1000);
	Write_CMD_LCD(0x01);


    esp01_connectAP();
    Write_CMD_LCD(0x01);

     while(1)
    {

/*************************************************************/     

   	//LM35

     Write_str_LCD("   LM35     ");
     Write_CMD_LCD(0xC0); 
	 Temp=ReadLM35();
     Write_int_LCD(Temp);
     Write_str_LCD("  degC");

     delay_ms(1000);

/*************************************************************/

    //MQ-2 SENSOR

      if(READBIT(IOPIN0,GAS)==0)
      {
	    Write_CMD_LCD(0x01);
	   	Write_str_LCD("Smoke Detected");
		Smoke=1;
      }
	  else
	  {
	    Write_CMD_LCD(0x01);
	    Write_str_LCD("No Smoke");
		Smoke=0;
	  }
      delay_ms(1000);
	  
	  Write_CMD_LCD(0x01);

/*************************************************************/

     //RTC DATE AND TIME

     //TIME
     Write_CMD_LCD(0x80);
     Write_DAT_LCD(HOUR/10+'0');  
   	 Write_DAT_LCD(HOUR%10+'0'); 
     Write_DAT_LCD(':');
     Write_DAT_LCD(MIN/10+'0');
     Write_DAT_LCD(MIN%10+'0');
     Write_DAT_LCD(':');
     Write_DAT_LCD(SEC/10+'0');
     Write_DAT_LCD(SEC%10+'0');

     //DATE
     Write_CMD_LCD(0xC0);		
     Write_DAT_LCD(DOM/10+'0'); 
     Write_DAT_LCD(DOM%10+'0');
     Write_DAT_LCD('/');
     Write_DAT_LCD(MONTH/10+'0');
     Write_DAT_LCD(MONTH%10+'0');
     Write_DAT_LCD('/');
     Write_DAT_LCD(YEAR/10+'0');
     Write_DAT_LCD(YEAR%10+'0');

     delay_ms(1000);
/*************************************************************/

	 Write_CMD_LCD(0x01);
	 
	 //converting int to string
	 sprintf(LM35,"%d",Temp); 
	 sprintf(MQ_2,"%d",Smoke);

/*************************************************************/
    //Data is sending to Thinkspeak 	 
	   
	  /*
	  if(MIN!=min_dummy)
      {
	      c++;
          min_dummy=MIN;
       }
	   if(c==1)
	   {
        flag=1;
	    esp01_sendToThingspeak(LM35); 
		c=0;         
	   }
      
        esp01_sendToThingspeak(MQ_2);
		*/
		
		if(MIN!=min_dummy)
      	{
	      c++;
          min_dummy=MIN;
	   		if(c==3)
	   		{
				Write_CMD_LCD(0x01);
				Write_str_LCD("LM35");
				delay_ms(1000);
	    		esp01_sendToThingspeak(LM35); 
				c=0;         
	   		}
      	}
		Write_CMD_LCD(0x01);
		Write_str_LCD("MQ_2");
		delay_ms(1000);
        esp01_sendToThingspeak_2(MQ_2);
	
/*************************************************************/
	    delay_ms(1000);
	    Write_CMD_LCD(0x01);
  }  
}
