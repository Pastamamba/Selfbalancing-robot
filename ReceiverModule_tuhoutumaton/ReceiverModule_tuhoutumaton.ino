// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

//RF Moduulin määrittelyt
const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

//Moottori 1
int mEnA = 9;    // Moottorin pyöritys. Pulssitetaan halutun nopeuden mukaan
int mIn1 = 4;    //Moottorin suunta. Asetetaan HIGH tai LOW tilaan halutun pyörimissuunnan mukaan
int mIn2 = 5;

//Moottori 2
int mEnB = 10;
int mIn3 = 7;
int mIn4 = 8;

int sensorXData;
int sensorYData;

char sensorXCharMsg[7];
char sensorYCharMsg[7];

void moto1Eteen()
{
  digitalWrite(mIn1, HIGH);
  digitalWrite(mIn2, LOW);
  analogWrite(mEnA, 200);
}

void moto2Eteen()
{
  digitalWrite(mIn3, HIGH);
  digitalWrite(mIn4, LOW);
  analogWrite(mEnB, 200);
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
  analogWrite(mEnB, 30);
}

void kaanto2()
{
  digitalWrite(mIn1, HIGH);
  digitalWrite(mIn2, LOW);
  digitalWrite(mIn3, HIGH);
  digitalWrite(mIn4, LOW);
  analogWrite(mEnA, 30);
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
    pinMode(led_pin, OUTPUT);  
    delay(1000);
    Serial.begin(9600);
    Serial.println("setup");

    // Initialise the IO and ISR
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

 // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	
	for (i = 0; i < buflen; i++)
	{
	  sensorXCharMsg[i] = char(buf[i]);
   sensorYCharMsg[i] = char(buf[i]);
     
     
     

	}
 sensorXCharMsg[buflen] = '\0';

 sensorXData = atoi(sensorXCharMsg);
 sensorYData = atoi(sensorYCharMsg);
 sensorXData = sensorXData;
 sensorYData = sensorYData;

 if(sensorXData > 703)
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

  if( sensorXData < 297)
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

 
 
	Serial.print(sensorXData);
  Serial.print("\t");
  Serial.println(sensorYData);
    }
    delay(5);
}
