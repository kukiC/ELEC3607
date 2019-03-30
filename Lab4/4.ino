#define blueToothSerial Serial2
#define led 13


//SoftwareSerial blueToothSerial(RxD,TxD);

void setup()
{
    Serial.begin(9600);

    pinMode(led, OUTPUT);
    setupBlueToothConnection();
}

void loop()
{
    String recvChar;
    
    while(1)
    {
        if(blueToothSerial.available())
        {//check if there's any data sent from the remote bluetooth shield
            recvChar = blueToothSerial.read();
            Serial.print(recvChar);

            if (recvChar.toInt() != 0){
              if (recvChar.toInt() % 2 == 0){
                Serial.print("OFF");
                digitalWrite(led, LOW);
                delay(1000);  
              }else{
                Serial.print("ON");
                digitalWrite(led, HIGH);
                delay(1000);
              }
            }else{
              Serial.print("Not digital");
            }
            


        }
    }
}

void setupBlueToothConnection()
{
    blueToothSerial.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=Xin\r\n");    // set the bluetooth name as "SeeedBTSlave"
    blueToothSerial.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    delay(2000);                                            // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
    blueToothSerial.flush();
}
