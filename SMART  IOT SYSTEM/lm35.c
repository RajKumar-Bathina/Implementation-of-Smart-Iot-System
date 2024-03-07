//lm35.c
#include "types.h"
#include "adc.h"
#include "adc_defines.h"

u32 ReadLM35(void)
{
  static u8 flag;
  if(flag==0)
  {
    Init_ADC();
	flag++;
  }						 
  return (Read_ADC(CH1)*100); //CALIBRATION EQN
}
