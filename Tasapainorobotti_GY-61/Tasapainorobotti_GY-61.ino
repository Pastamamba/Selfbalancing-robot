#include <Wire.h>
#define OFFSET 1
#define NEGOFFSET -1

extern float degX;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  motoSetup();
}

void loop()
{
  callSensor();
  float pulssi;// = pulssiLaskenta(degX);
  
  if(degX > OFFSET)
  {
    pulssi = pulssiLaskenta(degX);
    moto1Eteen(pulssi);
    moto2Eteen(pulssi); 
  }
  
  if(degX < NEGOFFSET)
  {
    pulssi = pulssiLaskenta(degX);
    moto1Taakse(pulssi);
    moto2Taakse(pulssi);
  }
  
  if (degX > NEGOFFSET && degX < OFFSET)
  {
    motoStop();
  }

  delay(2);
}
