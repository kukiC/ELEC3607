#define SSDSIZE 7       // number of segments in SSD
#define DIGSIZE 10      // number of different symbols to decode

const int pin = 9;
volatile unsigned int inum = 0;


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
  ssddecode(inum % 10);
  }

void inc(void)
{
  inum++;
}
 
 // the setup routine runs once when you press reset:
 void setup() {
  int  j;

  for (j = 0; j < SSDSIZE; j++){
    pinMode(ssdpin(j), OUTPUT);
  }

  attachInterrupt(pin, inc, FALLING);    

  }
