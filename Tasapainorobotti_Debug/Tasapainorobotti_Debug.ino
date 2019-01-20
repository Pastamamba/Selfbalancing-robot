#include <Wire.h>
#include <math.h>

#define OFFSET 0.1
#define NEGOFFSET 0.1

extern float complDegX;
extern float cAccX;
extern float cGyroX;
extern float accDegX;

extern const float kp;                        
extern const float ki;                           
extern const float kd;

float pulssi = 0;

float complFilterArvo[50];
float kalibrKiihtyvyysX[50];
float kalibrGyroX[50];
float kiihtyvyysKulmaX[50];
int nayteAika[50];

float proportionalKerroin = kp;
float integralKerroin = ki;
float derivativeKerroin = kd;

float moottorinOhjausPulssi[50];

int i = 0;

int testiAika = 0;
int lastAika;
int kokoAika;

void setup()
{
  Serial.begin(9600);
  setupSensor();
  motoSetup();
}

void loop()
{
  kokoAika = millis();
  
  callSensor();
  
  if(complDegX < NEGOFFSET)
  {
    pulssi = pulssiLaskenta(complDegX);
    moto1Eteen(pulssi);
    moto2Eteen(pulssi); 
  }
  
  if(complDegX > OFFSET)
  {
    pulssi = pulssiLaskenta(complDegX);
    moto1Taakse(pulssi);
    moto2Taakse(pulssi);
  }
  
  if (complDegX < OFFSET && complDegX > NEGOFFSET)
  {
    motoStop();
  }


  if(kokoAika - testiAika >= 100)
  {
    testiAika = kokoAika;
  complFilterArvo[i] = complDegX;
  kalibrKiihtyvyysX[i] = cAccX;
  kalibrGyroX[i] = cGyroX;
  kiihtyvyysKulmaX[i] = accDegX;
  moottorinOhjausPulssi[i] = pulssi;
  nayteAika[i] = millis();
  i++;
  }

  if(millis() - lastAika >= 5000)
  {
    lastAika = millis();
    motoStop();
    for(int a = 0; a < 50; a++)
    {
      Serial.print(nayteAika[a]); Serial.print(" "); Serial.print(complFilterArvo[a]); Serial.print(" "); Serial.print(kalibrKiihtyvyysX[a]); Serial.print(" "); Serial.print(kalibrGyroX[a]); 
      Serial.print(" "); Serial.print(kiihtyvyysKulmaX[a]); Serial.print(" "); Serial.print(moottorinOhjausPulssi[a]); Serial.print(" ");
      Serial.print(proportionalKerroin); Serial.print(" "); Serial.print(integralKerroin); Serial.print(" "); Serial.println(derivativeKerroin);
    }
    i = 0;
  }
  
  
  
  
}
