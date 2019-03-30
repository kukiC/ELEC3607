#define RX 16
#define TX 17


void setup() {
  Serial2.begin(38400);
  Serial.begin(38400);
  Serial2.println("HELLO");
//  USART1->US_MR |= US_MR_CHMODE_LOCAL_LOOPBACK;
}

void loop() {
  REG_USART1_MR |= US_MR_CHMODE_LOCAL_LOOPBACK;

  if(Serial2.available()>0){
    Serial.write(Serial2.read());
  }

}
