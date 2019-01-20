// SCL -> A5 & SDA -> A4

const int MPU_addr=0x68;

const float scaleAcc = 16384; // 2 g
const float scaleGyro = 131;  // 250 dgr
const float gyroOffset = 2.7;

const float maxAccX = 1;
const float minAccX = -1;

int sensorAccX;
int sensorGyroX;

float cAccX = 0;
float cGyroX = 0;

float accDegX = 0;
float complDegX = 0;

unsigned long timer = 0;

void setupSensor()
{
  Wire.begin();
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 rekisteri
  Wire.write(0);    // Wake up
  Wire.endTransmission(true);
 
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B); // GYRO_CONFIG rekisteri
  Wire.write(0);
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C); // ACCEL_CONFIG rekisteri
  Wire.write(0);
  Wire.endTransmission(true);
}

void initAccTransfer()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);                  // Aloitusrekisteri
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true); // Pyydä N määrä rekistereitä
}

void initGyroTransfer()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);                  // Aloitusrekisteri
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true); // Pyydä N määrä rekistereitä
}

void readValues()
{
  initAccTransfer();
  sensorAccX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  initGyroTransfer();
  sensorGyroX=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
}

void calculateValues()
{  
  cAccX = sensorAccX / scaleAcc; // Kalibroi skaalavakiolla
  cGyroX = sensorGyroX / scaleGyro + gyroOffset;

  if(cAccX > maxAccX) { // Max määrittely
    cAccX = maxAccX;
  }
  if(cAccX < minAccX) { // Min määrittely
    cAccX = minAccX;
  }
  
  accDegX = asin(cAccX) * 180 / M_PI; // Kiihtyvyysarvolla laskettu asento

  complDegX = 0.98 * (complDegX + cGyroX * ((double)micros() - timer)/1000000) + 0.02 * (accDegX); // Suodatin
  timer = micros();
  delay(2);
}

void printValues()
{
  Serial.print(sensorAccX); Serial.print("\t;");
  Serial.print(sensorGyroX); Serial.print("\t;");
  Serial.print(cAccX); Serial.print("\t;");
  Serial.print(cGyroX); Serial.print("\t;");
  Serial.print(accDegX); Serial.print("\t;");
  Serial.println(complDegX);
}

void callSensor()
{
  readValues();
  calculateValues();
  //printValues(); // DEBUG
}
