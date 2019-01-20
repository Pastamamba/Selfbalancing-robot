#include <Wire.h>
#include <math.h>

#define OFFSET 1
#define NEGOFFSET -1

extern float complDeg;

float pulssi = 0;

void setup()
{
  Serial.begin(9600);
  setupSensor();
  motoSetup();
}

void loop()
{
  callSensor();
  
  if(complDeg < NEGOFFSET)
  {
    pulssi = pulssiLaskenta(complDeg);
    moto1Eteen(pulssi);
    moto2Eteen(pulssi); 
  }
  
  if(complDeg > OFFSET)
  {
    pulssi = pulssiLaskenta(complDeg);
    moto1Taakse(pulssi);
    moto2Taakse(pulssi);
  }
  
  if (complDeg < OFFSET && complDeg > NEGOFFSET)
  {
    motoStop();
  }
}
