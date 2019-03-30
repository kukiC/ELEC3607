#define  XTC    TC1       // TC number
#define  XCHAN  2         // TC channel
#define  XID    ID_TC5    // Instance ID
#define VARIANT_MCK 84000000

 void sprint(char *s) {
   Serial.print(s);
 }

 void fprint(double f) {
   Serial.println(f);
}


void setup(){
  Serial.begin(9600);
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_Start(XTC, XCHAN);
 }

void loop(){
  TC_Start(XTC, XCHAN);
  sprint("HELLO");
  t_sp = TC_ReadCV(XTC, XCHAN), DEC);
  Serial.println((double)t_sp / VARIANT_MCK);
  delay(1000);

  TC_Start(XTC, XCHAN);
  fprint(1.2);
  t_fp = TC_ReadCV(XTC, XCHAN), DEC);
  Serial.println((double)t_fp / VARIANT_MCK);
}
