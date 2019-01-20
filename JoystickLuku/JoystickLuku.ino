/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int xAxisPin = A0;  // Analog input pins that the joystick is attached to
const int yAxisPin = A1;
const int switchPin = A2; 

int xAxisValue = 0;        // value read from the pot
int yAxisValue = 0;
int switchValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);  
  Serial.print("X-Axis");
  Serial.print("\tY-Axis");
  Serial.println("\tSwitch");
}

void loop() {
  // read the analog in value:
  xAxisValue = analogRead(xAxisPin);
  yAxisValue = analogRead(yAxisPin);
  switchValue = analogRead(switchPin);
  
  
  
  

  // print the results to the Serial Monitor:

  Serial.print(xAxisValue-503);
  Serial.print("\t");
  Serial.print(yAxisValue-507);
  Serial.print("\t");
  if(switchValue == 0)
  {
  Serial.println("On");
  }
  else
  {
    Serial.println("Off");
  }
  delay(2);
}
