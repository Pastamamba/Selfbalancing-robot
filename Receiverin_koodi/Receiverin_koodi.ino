#include "RH_ASK.h"
#include "SPI.h" // Tarvitaan kääntämiseen
RH_ASK driver;

void setup()
{
    Serial.begin(9600);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) 
    {
	int i;

	Serial.print(":");
	Serial.println((char*)buf);
    }
}
