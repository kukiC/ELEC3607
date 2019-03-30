#define  XTC    TC1       // TC number
#define  XCHAN  2         // TC channel
#define  XID    ID_TC5    // Instance ID

void setup(){
  Serial.begin(9600);
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK2);
  TC_Start(XTC, XCHAN);
 }

void loop(){
  TC_Start(XTC, XCHAN);
  delay(1000);
  Serial.println(TC_ReadCV(XTC, XCHAN), DEC);
}
