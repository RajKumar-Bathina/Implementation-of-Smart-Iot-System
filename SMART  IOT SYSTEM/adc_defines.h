//adc_defines.h

#define PINFUNC2 1
#define AIN0 PINFUNC2
#define AIN1 PINFUNC2
#define AIN2 PINFUNC2
#define AIN3 PINFUNC2


//#define FOSC        	12000000
//#define CCLK        	(5*FOSC)
//#define PCLK        	CCLK/4
#define ADCLK       	3750000

//defines for ADCR
#define CH0 0x01
#define CH1 0x02
#define CH2 0x04
#define CH3 0x08

#define CHANNEL_SEL 	CH1
#define CLKDIV_BITS     (((PCLK/ADCLK)-1)<<8)	
#define PDN_BIT     	 21
#define ADC_START_BIT    24

//defines for ADDR
#define ADC_DATA_BIT     6
#define DONE_BIT     	 31
