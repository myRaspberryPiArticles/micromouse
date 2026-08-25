// Gemini MPU6500/9250 module
// `initMpu()` sets up the pins and I2C
// Use `updateMpu()` in an interrupt or core 2
// Value is updated to float `heading`

#include <Wire.h>
#include "FastIMU.h" 

// FIXED: Removed the ampersand '&' to pass by reference
MPU6500 mpu(Wire1); 

float gyroBiasZ = 0.0;
unsigned long lastTime = 0;

float pitch = 0.0; // The filter works best on Pitch/Roll
const float alpha = 0.98; // Filter coefficient (98% gyro, 2% accelerometer)

void initMpu() {
  Wire1.setSDA(6);
  Wire1.setSCL(7);
  Wire1.begin();
  Wire1.setClock(400000);

  int err = mpu.init(calData(), 0x68);
  if (err != 0) {
    Serial1.print("MPU init failed with error code: ");
    Serial1.println(err);
    while (1) delay(10);
  }

  mpu.setGyroRange(500); // 500 DPS
  
  // FIXED: Changed to the correct FastIMU method name
  mpu.setGyroLPF(3); 
  
  Serial1.println("MPU INIT SUCCESSFUL!");
}

void resetHeading() {
  int samples = 500;
  double sum = 0;
  GyroData gyroData;

  for (int i = 0; i < samples; i++) {
    mpu.update();
    mpu.getGyro(&gyroData);
    sum += gyroData.gyroZ; 
    delay(2);
  }
  
  gyroBiasZ = sum / samples;
  heading = 0.0;
  lastTime = micros(); 
}

void resetHeadingVariable() {
  heading = 0.0;
}

void updateMpu() {
  GyroData gyroData;
  mpu.update();
  mpu.getGyro(&gyroData);

  unsigned long now = micros();
  if (lastTime == 0) lastTime = now; 
  float dt = (now - lastTime) / 1000000.0;
  lastTime = now;

  // 1. Corrected to use your existing gyroBiasZ variable
  float rateZ = gyroData.gyroZ - gyroBiasZ; 
  
  // 2. Strict noise deadband using fabsf() for floats
  // If the rotation rate is tiny, force it to 0 so it doesn't accumulate drift
  float noiseThreshold = 1.855; // Adjust this up to 0.8 if it still creeps when still
  if (fabsf(rateZ) < noiseThreshold) {
    rateZ = 0.0;
  }
  
  // 3. Integrate the cleaned rate into your heading
  float delta = rateZ * dt;   
  heading += delta;       
  globalHeading += delta; 
  
  //Serial1.print("Heading: ");
  //Serial1.print(heading);
  //Serial1.println("º");
}
