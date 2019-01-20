// SCL -> A5 & SDA -> A4

const int MPU_addr=0x68;

const float scaleAcc = 16384; // +-2 g
const float scaleGyro = 131;  // +-250 dgr

int initCheck = 0;

int sensorAccX;
int sensorAccY;
int sensorAccZ;

int sensorGyroX;
int sensorGyroY;
int sensorGyroZ;

float cAccX = 0;
float cAccY = 0;
float cAccZ = 0;

float cGyroX = 0;
float cGyroY = 0;
float cGyroZ = 0;

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
  Wire.requestFrom(MPU_addr,6,true);  // request N registers
}

void initGyroTransfer() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // start register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);  // request N registers
}

void printFirstRun() {
  Serial.print("sAccX ");
  Serial.print("| sAccY ");
  Serial.print("| sAccZ ");
  Serial.print("| sGyroX ");
  Serial.print("| sGyroY ");
  Serial.print("| sGyroZ ");
  Serial.print("| cAccX ");
  Serial.print("| cAccY ");
  Serial.print("| cAccZ ");
  Serial.print("| cGyroX ");
  Serial.print("| cGyroY ");
  Serial.println("| cGyroZ ");
}

void readValues() {
  initAccTransfer();
  sensorAccX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  sensorAccY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  sensorAccZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 
  initGyroTransfer();
  sensorGyroX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  sensorGyroY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  sensorGyroZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void scaleValues() {  
  cAccX = sensorAccX / scaleAcc; // calibrate values using scale factor
  cAccY = sensorAccY / scaleAcc;
  cAccZ = sensorAccZ / scaleAcc;

  cGyroX = sensorGyroX / scaleGyro;
  cGyroY = sensorGyroY / scaleGyro;
  cGyroZ = sensorGyroZ / scaleGyro;
}

void printValues() {
  Serial.print(sensorAccX); Serial.print("\t;");
  Serial.print(sensorAccY); Serial.print("\t;");
  Serial.print(sensorAccZ); Serial.print("\t;");
  Serial.print(sensorGyroX); Serial.print("\t;");
  Serial.print(sensorGyroY); Serial.print("\t;");
  Serial.print(sensorGyroZ); Serial.print("\t;");
  Serial.print(cAccX); Serial.print("\t;");
  Serial.print(cAccY); Serial.print("\t;");
  Serial.print(cAccZ); Serial.print("\t;");
  Serial.print(cGyroX); Serial.print("\t;");
  Serial.print(cGyroY); Serial.print("\t;");
  Serial.println(cGyroZ);
}

void callSensor() {
  if (initCheck == 0) {
    delay(500);
    printFirstRun();
    initCheck = 1;
  }
  readValues();
  scaleValues();
  printValues();
  delay(10);
}
