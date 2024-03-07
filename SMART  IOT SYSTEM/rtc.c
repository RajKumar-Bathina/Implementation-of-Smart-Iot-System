//rtc.c
#include<LPC21xx.h>

void rtc_init()
{
		         SEC=00; //Initialized seconds
                 MIN=15; //Initialized minutes
                 HOUR=9;//Initialized hour
                 
                 DOM=19;
                 MONTH=01;
                 YEAR=24;
}
