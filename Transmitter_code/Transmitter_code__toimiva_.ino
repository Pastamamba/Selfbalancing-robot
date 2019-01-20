  
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
const int SensorXPin = A0;
const int SensorYPin = A2;
int SensorXData;
int SensorYData;
int a = 0;
char SensorXCharMsg[6];
char SensorYCharMsg[6];
void setup()
{
  Serial.begin(9600);
  
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); 
  vw_setup(2000);   
}

byte count = 1;

void loop()
{
  SensorXData = analogRead(SensorXPin)+1;
  SensorYData = analogRead(SensorYPin)+1025;
  if (SensorXData < 400 || SensorXData > 600)
  {
  itoa(SensorXData,SensorXCharMsg,10);
 Serial.print("SensorX Integer: ");
  Serial.print(SensorXData);
  Serial.print(" SensorX CharMsg: ");
  Serial.print(SensorXCharMsg);
  Serial.print("\t");
  Serial.println(" ");
  }
  if (SensorYData < 1400 || SensorYData > 1600)
  {
itoa(SensorYData,SensorYCharMsg,10);
  Serial.print("SensorY Integer: ");
  Serial.print(SensorYData);
  Serial.print("\t");
  Serial.print(" SensorY CharMsg: ");
  Serial.print(SensorYCharMsg);
  Serial.println(" ");
  }
  delay(50);
  

  if (SensorXData < 400 || SensorXData > 600)
  {
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  
  vw_send((uint8_t *)SensorXCharMsg, strlen(SensorXCharMsg));
  vw_wait_tx(); // Wait until the whole message is gone
  }
  
  else if (SensorYData < 1400 || SensorYData > 1600)
  {
    digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)SensorYCharMsg, strlen(SensorYCharMsg));
  vw_wait_tx(); // Wait until the whole message is gone
  }
  else 
  {
    itoa(a,SensorYCharMsg,10);
      vw_send((uint8_t *)SensorYCharMsg, strlen(SensorYCharMsg));
  vw_wait_tx(); // Wait until the whole message is gone
    
  }
  digitalWrite(led_pin, LOW);
  delay(50);
}


