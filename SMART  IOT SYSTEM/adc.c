//adc.c
#include<LPC21xX.H>
#include "delay.h"
#include "types.h"
#include "defines.h"
#include "adc_defines.h"
#include "adc.h"
#include "uart0.h"

#define CFGPIN(WORD,PIN,FUNC)   (WORD=((PIN<16)?((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))):((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2)))))

void Init_ADC(void)
{
  //configure P0.28 for alt fun AINO
  CFGPIN(PINSEL1,28,AIN1);
  ADCR=1<<PDN_BIT|CLKDIV_BITS|CHANNEL_SEL;
}								   

f32 Read_ADC(u8 chNo)
{
  u16 adcVal=0; f32 eAR;
  WRITEBYTE(ADCR,0,chNo);
  SETBIT(ADCR,ADC_START_BIT);
  delay_ms(1000);
  while(!READBIT(ADDR,DONE_BIT));
  CLRBIT(ADCR,ADC_START_BIT);
  adcVal=((ADDR>>ADC_DATA_BIT)&0x3FF);
  eAR=(adcVal*(3.3/1023));
  
  return eAR;
}
