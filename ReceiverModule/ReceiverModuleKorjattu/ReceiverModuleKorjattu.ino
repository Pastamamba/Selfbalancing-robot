#include "VirtualWire.h"

//RF Moduulin määrittelyt
const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

//Moottori 1
int mEnA = 5;    // Moottorin pyöritys. Pulssitetaan halutun nopeuden mukaan
int mIn1 = 3;    //Moottorin suunta. Asetetaan HIGH tai LOW tilaan halutun pyörimissuunnan mukaan
int mIn2 = 4;

//Moottori 2
int mEnB = 6;
int mIn3 = 7;
int mIn4 = 8;

int sensorData; //Tallennetaan vastaanotettava data

char sensorXCharMsg[7]; //Vastaan otettava data char muodossa

void moto1Eteen()
{
  digitalWrite(mIn1, HIGH);
  digitalWrite(mIn2, LOW);
  analogWrite(mEnA, 255);
}

void moto2Eteen()
{
  digitalWrite(mIn3, HIGH);
  digitalWrite(mIn4, LOW);
  analogWrite(mEnB, 255);
}

void motoStop()
{
  digitalWrite(mIn1, LOW);
  digitalWrite(mIn2, LOW);
  digitalWrite(mIn3, LOW);
  digitalWrite(mIn4, LOW);
}

void moto1Taakse()
{
  digitalWrite(mIn1, LOW);
  digitalWrite(mIn2, HIGH);
  analogWrite(mEnA, 200);
}

void moto2Taakse()
{
  digitalWrite(mIn3, LOW);
  digitalWrite(mIn4, HIGH);
  analogWrite(mEnB, 200);
}

void kaanto1()
{
  digitalWrite(mIn1, HIGH);
  digitalWrite(mIn2, LOW);
  digitalWrite(mIn3, HIGH);
  digitalWrite(mIn4, LOW);
  analogWrite(mEnA, 200);
  analogWrite(mEnB, 200);
}

void kaanto2()
{
  digitalWrite(mIn1, HIGH);
  digitalWrite(mIn2, LOW);
  digitalWrite(mIn3, HIGH);
  digitalWrite(mIn4, LOW);
  analogWrite(mEnA, 200);
  analogWrite(mEnB, 200);
}

void setup()
{
  pinMode(mEnA, OUTPUT);
  pinMode(mEnB, OUTPUT);
  pinMode(mIn1, OUTPUT);
  pinMode(mIn2, OUTPUT);
  pinMode(mIn3, OUTPUT);
  pinMode(mIn4, OUTPUT);
    Serial.begin(9600);

    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true);
    vw_setup(2000);	 // Bittejä sekunnissa

    vw_rx_start();       // Vastaanoton aloitus
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
	
	for (i = 0; i < buflen; i++)
	{
	  sensorXCharMsg[i] = char(buf[i]);
	}
 sensorXCharMsg[buflen] = '\0';

 sensorData = atoi(sensorXCharMsg); //Muunnetaan saatu char data int muotoon
 Serial.println(sensorData);


    }

 if(sensorData > 703 && sensorData <= 1024)
  {
   moto1Eteen();
   moto2Eteen();
   //digitalWrite(led_pin, HIGH);

  }

  else
  {
    //digitalWrite(led_pin, LOW);
    motoStop();

  }

  if( sensorData < 297 && sensorData > 0)
  {
    //digitalWrite(led_pin, HIGH);
    moto1Taakse();
    moto2Taakse();
  }

  else
  {
    //digitalWrite(led_pin, LOW);
    motoStop();
  }

  if(sensorData > 1700)
  {
    kaanto1();
  }

  if(sensorData < 1300 && sensorData >= 1025)
  {
   kaanto2(); 
  }
}


