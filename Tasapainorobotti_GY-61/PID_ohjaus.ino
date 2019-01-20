const int pulssiMax = 255;
const int pulssiMin = 120;

const float kp = 25;                          //Proportionaalinen kerroin
const float ki = 0;                           //Integraalinen kerroin
const float kd = 0;                           //Derivaatallinen kerroin

float aika, timePrev, elapsedTime;

float prevError;

float pulssiLaskenta(float sensArvo)
{
 // Serial.print("Pulssilaskenta aloitus");Serial.print("\t");Serial.println(millis());
  timePrev = aika;
  aika = millis();
  elapsedTime = (aika - timePrev) / 1000;
  float error =/* haluttArvo -*/ sensArvo;   //Määritellään virhe jota pyritään korjaamaan
  float PID_Integral = 0;

  float PID_Proportional = error * kp;
  PID_Integral += (ki * error);
  float PID_Derivative = kd * ((error - prevError)/elapsedTime);
  float output = PID_Proportional + PID_Integral + PID_Derivative;

  if(output < 0) output = output * (-1);      //Muunnetaan arvot positiivisiksi
  if(output < pulssiMin) output = pulssiMin;              //Annetaan moottorille pienin pwm arvo jolla se jaksaa liikkua
  if (output > pulssiMax) output = pulssiMax; //rajoitetaan pwm maksimiarvo


  prevError = error;
  //Serial.print("pulssilaskentalopetus");Serial.print("\t");Serial.println(millis());
  return output;
}

