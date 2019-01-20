#include <Wire.h>
#include <math.h>

#define OFFSET 1
#define NEGOFFSET -1

extern float complDegX;

float pulssi = 0;

void setup()
{
  //Serial.begin(9600); // DEBUG
  setupSensor();
  setupMotors();
}

void loop()
{
  callSensor();
  
  if(complDegX > OFFSET) {
    pulssi = pulssiLaskenta(complDegX);
    moto1Taakse(pulssi);
    moto2Taakse(pulssi);
  }
  if(complDegX < NEGOFFSET) {
    pulssi = pulssiLaskenta(complDegX);
    moto1Eteen(pulssi);
    moto2Eteen(pulssi); 
  }
  if (complDegX < OFFSET && complDegX > NEGOFFSET) {
    motoStop();
  }
}
