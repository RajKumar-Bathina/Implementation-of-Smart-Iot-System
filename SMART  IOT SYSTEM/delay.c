
void delay_us(unsigned int dlyUs)
{
  dlyUs*=12;
  while(dlyUs--);
}
 void delay_ms(unsigned int dlyms)
{
  dlyms*=12000;
  while(dlyms--);
}

void delay_s(unsigned int dlys)
{
  dlys*=12000000;
  while(dlys--);
}

