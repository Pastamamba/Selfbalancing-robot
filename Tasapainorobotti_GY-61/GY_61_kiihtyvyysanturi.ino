#include <math.h>

#define DEGOFFSET 0

const int analogInPinX = A0;

const float factor = 0.3;
const float calibrAccX[2] = {0.1464, 48.119};

float filtSensValueX = 0;
float lastFiltSensValueX = 0;

float lastMillis = 0;

float sensorAccX = 0;
float cAccX = 0;
float degX = 0;

void setPeakValues() {
  cAccX = min(9.81, cAccX);
  cAccX = max(-9.81, cAccX);
}

void readValues() {
  sensorAccX = analogRead(analogInPinX);
}

void calculateValues() {
  filtSensValueX = (factor * sensorAccX) + ((1 - factor) * lastFiltSensValueX);
  lastFiltSensValueX = filtSensValueX;

  cAccX = calibrAccX[0] * lastFiltSensValueX - calibrAccX[1];

  setPeakValues();
  degX = asin(cAccX / 9.81) * 180 / M_PI - DEGOFFSET;
}

void printValues() {
  Serial.print(cAccX); Serial.print("\t;");
  Serial.print(degX); Serial.print("\t;");
  Serial.print(sensorAccX); Serial.print("\t");
  Serial.print(lastFiltSensValueX); Serial.print("\t");
  Serial.println(millis());
}

void callSensor() {
  readValues();
  calculateValues();
  printValues();
  delay(2);
}
