// SCL -> A5 & SDA -> A4

#define ACCYOFFSET 16

const int MPU_addr=0x68;

const float scaleAcc = 16384; // +-2 g
const float scaleGyro = 131;  // +-250 dgr

const float maxAccX = 1;
const float minAccX = -1;
const float maxAccY = 1;
const float minAccY = -1;

int sensorAccX;
int sensorAccY;
int sensorGyroX;

float cAccX = 0;
float cAccY = 0;
float cGyroX = 0;

float accDegX = 0;
float accDegY = 0;
float complDeg = 0;

unsigned long timer = 0;

void setupSensor() {
  Wire.begin();
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Wake up
  Wire.endTransmission(true);
 
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);  // GYRO_CONFIG register
  Wire.write(0);
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);  // ACCEL_CONFIG register
  Wire.write(0);
  Wire.endTransmission(true);
}

void initAccTransfer() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // start register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,4,true);  // request N registers
}

void initGyroTransfer() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // start register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);  // request N registers
}

void readValues() {
  initAccTransfer();
  sensorAccX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  sensorAccY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L
  initGyroTransfer();
  sensorGyroX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
}

void calculateValues() {  
  cAccX = sensorAccX / scaleAcc; // calibrate values using scale factor
  cAccY = sensorAccY / scaleAcc; // calibrate values using scale factor
  cGyroX = sensorGyroX / scaleGyro + 2.7;
  
  if(cAccX > maxAccX) {
    cAccX = maxAccX;
  }
  if(cAccX < minAccX) {
    cAccX = minAccX;
  }
  if(cAccY > maxAccY) {
    cAccY = maxAccY;
  }
  if(cAccY < minAccY) {
    cAccY = minAccY;
  }
  
  accDegX = asin(cAccX) * 180 / M_PI;  // calculate accelerometer angle
  accDegY = atan2(cAccY, cAccX) * 180 / M_PI;

  complDeg = 0.98 * (complDeg + cGyroX * ((double)micros() - timer)/1000000) + 0.02 * (accDegY);
  timer = micros();
  delay(2);
}

void printValues() {
  Serial.print(sensorAccX); Serial.print("\t;");
  Serial.print(sensorAccY); Serial.print("\t;");
  Serial.print(sensorGyroX); Serial.print("\t;");
  Serial.print(cAccX); Serial.print("\t;");
  Serial.print(cAccY); Serial.print("\t;");
  Serial.print(cGyroX); Serial.print("\t;");
  Serial.print(accDegX); Serial.print("\t;");
  Serial.print(accDegY); Serial.print("\t;");
  Serial.println(complDeg);
}

void callSensor() {
  readValues();
  calculateValues();
  printValues();
}
