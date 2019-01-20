const int pulssiOff = 0;

//Moottori 1
int mEnA = 5; // Moottorin pyöritys. Pulssitetaan halutun nopeuden mukaan
int mIn1 = 3; // Moottorin suunta. Asetetaan HIGH tai LOW tilaan halutun pyörimissuunnan mukaan
int mIn2 = 4;

//Moottori 2
int mEnB = 6;
int mIn3 = 7;
int mIn4 = 8;

void setupMotors() 
{
  pinMode(mEnA, OUTPUT);
  pinMode(mEnB, OUTPUT);
  pinMode(mIn1, OUTPUT);
  pinMode(mIn2, OUTPUT);
  pinMode(mIn3, OUTPUT);
  pinMode(mIn4, OUTPUT);
}

void moto1Eteen(int pulssi)
{
  digitalWrite(mIn1, HIGH);
  digitalWrite(mIn2, LOW);
  analogWrite(mEnA, pulssi);
}

void moto2Eteen(int pulssi)
{
  digitalWrite(mIn3, HIGH);
  digitalWrite(mIn4, LOW);
  analogWrite(mEnB, pulssi);
}

void motoStop()
{
  analogWrite(mEnA, pulssiOff);
  analogWrite(mEnB, pulssiOff);
}

void moto1Taakse(int pulssi)
{
  digitalWrite(mIn1, LOW);
  digitalWrite(mIn2, HIGH);
  analogWrite(mEnA, pulssi);
}

void moto2Taakse(int pulssi)
{
  digitalWrite(mIn3, LOW);
  digitalWrite(mIn4, HIGH);
  analogWrite(mEnB, pulssi);
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
