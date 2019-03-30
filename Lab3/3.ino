#define  XTC    TC0       // TC number
#define  XCHAN  0         // TC channel
#define  XID    ID_TC0    // Instance ID
#define  PIN    2
#define  PINCHAN  25      // Digital pin 2 which is on PIOB channel 25

void pwmwave(unsigned int duty, unsigned int freq) {
  unsigned int  tcclk = VARIANT_MCK / freq / 2;
//  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPA_SET);
  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_TOGGLE | TC_CMR_ACPC_SET| TC_CMR_ACPA_CLEAR);
  TC_SetRC(XTC, XCHAN, tcclk);
  TC_SetRA(XTC, XCHAN, tcclk*duty/100);

  TC_Start(XTC, XCHAN);

}

void squarewave(unsigned int freq) {
  unsigned int  tcclk = VARIANT_MCK / freq / 4;

  TC_Configure(XTC, XCHAN, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_ACPC_TOGGLE);
  TC_SetRC(XTC, XCHAN, tcclk);
  TC_Start(XTC, XCHAN);
  }

void setup() {
  unsigned int chanmask = (1 << PINCHAN);
    
  Serial.begin(9600);

  // set PIO to chan A
  REG_PIOB_PDR = chanmask;
  REG_PIOB_ABSR = chanmask;
  REG_PIOB_MDDR = chanmask;

  // set up TC
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(XID);
//  squarewave(100000);
  pwmwave(20, 50000);
  }
  void dreg(char *s, unsigned int r) {
  Serial.print(s);
  Serial.print(r, HEX);
  }

  void tcregs()
  {
  dreg("\n CV: ", XTC->TC_CHANNEL[XCHAN].TC_CV);  
  dreg(" SR: ", XTC->TC_CHANNEL[XCHAN].TC_SR);
  dreg(" CMR: ", XTC->TC_CHANNEL[XCHAN].TC_CMR);
  dreg(" RA: ", XTC->TC_CHANNEL[XCHAN].TC_RA);
  dreg(" RC: ", XTC->TC_CHANNEL[XCHAN].TC_RC);
  }

  void loop() {
  tcregs();
  }
