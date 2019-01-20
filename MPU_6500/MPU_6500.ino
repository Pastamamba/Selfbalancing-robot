#include <Wire.h>

void setup(){
  setupSensor();  
  Serial.begin(9600);
}

void loop(){
  callSensor();
}

