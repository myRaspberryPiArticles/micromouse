// ============================================================
//  MPU6500/9250 gyroscope (FastIMU library)
//    initMpu()      — set up I2C + the chip
//    resetHeading() — average the resting bias, zero `heading`
//    updateMpu()    — integrate one step (call from a fast loop)
//    heading        — current yaw in degrees (zeroed by resetHeading)
//    globalHeading  — same integration but never reset (debug)
// ============================================================

#include <Wire.h>
#include "FastIMU.h"

MPU6500 mpu(Wire1);

float gyroBiasZ = 0.0;
unsigned long lastTime = 0;

// Rotation rates smaller than this are treated as noise (prevents drift).
const float GYRO_NOISE_THRESHOLD = 1.855;

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

  mpu.setGyroRange(500);  // ±500 DPS
  mpu.setGyroLPF(3);

  Serial1.println("MPU INIT SUCCESSFUL!");
}

// Average 500 gyro readings to find the resting bias, then zero heading.
void resetHeading() {
  const int samples = 500;
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

  // Remove the calibrated bias, then zero out tiny rates (noise deadband)
  float rateZ = gyroData.gyroZ - gyroBiasZ;
  if (fabsf(rateZ) < GYRO_NOISE_THRESHOLD) {
    rateZ = 0.0;
  }

  // Integrate the cleaned rate into both headings
  float delta = rateZ * dt;
  heading += delta;
  globalHeading += delta;
}
