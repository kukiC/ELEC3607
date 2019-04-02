#define SSDSIZE 7       // number of segments in SSD
#define DIGSIZE 10      // number of different symbols to decode

const int pin = 9;
volatile unsigned int inum = 1;
int counter = 0;

int ssdtab[DIGSIZE][SSDSIZE] =
 {{1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}};

#define  ssdpin(i)  (i+2) // a to pin 2, b to pin 3 etc so the pin offset is +2

void ssddecode(int a){
  int j;
  for (j = 0; j < SSDSIZE; j++)
    digitalWrite(ssdpin(j),  ssdtab[a][j] == 1 ? HIGH : LOW);
  }

void loop(){
  if(inum){
    counter++;
  }else{
    counter--;
    if(counter == -1)
      counter = 9;
    }
  ssddecode(counter % 10);
  delay(1000);
  }

void inc(void)
{
  inum = !inum;
}
 
 // the setup routine runs once when you press reset:
 void setup() {
  int  j;

  for (j = 0; j < SSDSIZE; j++){
    pinMode(ssdpin(j), OUTPUT);
  }

  attachInterrupt(pin, inc, FALLING);    

  }
