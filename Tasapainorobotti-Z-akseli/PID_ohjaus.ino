const int pulssiMax = 255;
const int pulssiMin = 80;

const float kp = 5;                          //Proportionaalinen kerroin
const float ki = 0.05;                           //Integraalinen kerroin
const float kd = 1;                           //Derivaatallinen kerroin

float aika, elapsedTime;
float timePrev = 0;

float PID_Integral = 0;
float prevError;
float errorSum = 0;

float pulssiLaskenta(float sensArvo)
{
  
  aika = millis();
  elapsedTime = (aika - timePrev);
  float error =/* haluttArvo -*/ sensArvo;   //Määritellään virhe jota pyritään korjaamaan
  

  float PID_Proportional = error * kp;                                //Suhteellinen funktio
  errorSum += (error * elapsedTime);                                       //Integraalinen funktio
  float PID_Derivative = kd * ((error - prevError)/elapsedTime);      //Derivatiivinen funktio
  PID_Integral = ki * errorSum;
  float output = PID_Proportional + PID_Integral + PID_Derivative;    //Lasketaan funktioiden summa, jota käytetään PWM signaalina moottoreille

  if(output < 0) output = output * (-1);      //Muunnetaan arvot positiivisiksi
  if(output < pulssiMin) output = pulssiMin;              //Annetaan moottorille pienin pwm arvo jolla se jaksaa liikkua
  if (output > pulssiMax) output = pulssiMax; //rajoitetaan pwm maksimiarvo


  prevError = error;
  timePrev = aika;
  return output;
}

