#include <Arduino.h>

// --- Motor Pins (DRV8833) ---
#define M_FORWARD   17
#define M_BACKWARD  16
#define SLP         20

// --- Encoder Pins ---
#define ENCODER_A 22
#define ENCODER_B 5

// Volatile allows ISR to modify it safely; signed long prevents overflow
volatile long encoderValue = 0;

// Dual encoder placeholders
volatile long leftEncoderValue = 0;
volatile long rightEncoderValue = 0;

const uint16_t PULSES_PER_MM = 18230;

// Forward Declarations
void encoderISR_A();
void encoderISR_B();
void setMotors(int speed);
void stop();

// --- Core Helper Functions ---

void resetEncoders() {
  noInterrupts();
  encoderValue = 0;
  leftEncoderValue = 0;
  rightEncoderValue = 0;
  interrupts();
}

long getEncoderValue() {
  noInterrupts();
  long val = encoderValue;
  interrupts();
  return val;
}

void printEncoders() {
  // Currently prints single encoder to both L R outputs as placeholder
  Serial.print(getEncoderValue());
  Serial.print(" ");
  Serial.println(getEncoderValue());
}

long calculateDistancePulses(float mm) {
  return (long)(mm * PULSES_PER_MM);
}

long calculateAnglePulses(float deg) {
  // Adjust scaling factor depending on your robot's wheelbase turn ratio
  return (long)(deg * 10.0); 
}

float pulsesToDistance(long pulses) {
  return (float)pulses / PULSES_PER_MM;
}

// --- Interrupt Service Routines ---

void encoderISR_A() {
  if (digitalRead(ENCODER_A) != digitalRead(ENCODER_B)) {
    encoderValue--;
  } else {
    encoderValue++;
  }
}

void encoderISR_B() {
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    encoderValue--;
  } else {
    encoderValue++;
  }
}

void initEncoders() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderISR_B, CHANGE);
}

// --- Motor Control Functions ---

void initMotors() {
  pinMode(M_FORWARD, OUTPUT);
  pinMode(M_BACKWARD, OUTPUT);
  pinMode(SLP, OUTPUT);

  // Enable DRV8833 driver chip
  digitalWrite(SLP, HIGH);
  stop();
}

void setMotors(int speed) {
  // Constrain input speed to valid PWM range (-255 to 255)
  speed = constrain(speed, -255, 255);
  int absSpeed = abs(speed);

  if (speed > 0) {
    // Drive Forward
    analogWrite(M_FORWARD, absSpeed);
    analogWrite(M_BACKWARD, 0);
  } 
  else if (speed < 0) {
    // Drive Backward
    analogWrite(M_FORWARD, 0);
    analogWrite(M_BACKWARD, absSpeed);
  } 
  else {
    // Stop / Coast
    stop();
  }
}

void stop() {
  analogWrite(M_FORWARD, 0);
  analogWrite(M_BACKWARD, 0);
}

// --- Movement Routines ---

void one_cell_forward() {
  resetEncoders();
  setMotors(255); // Drive Forward
  
  while (abs(getEncoderValue()) < PULSES_PER_MM) {
    // Wait for target distance
  }
  stop();
}

void half_cell_forward() {
  resetEncoders();
  setMotors(255); // Drive Forward
  
  while (abs(getEncoderValue()) < (PULSES_PER_MM / 2)) {
    // Wait for target distance
  }
  stop();
}

void backup() {
  resetEncoders();
  setMotors(-255); // Drive Backward
  
  while (abs(getEncoderValue()) < 3169) {
    // Wait until target pulses are counted in reverse
  }
  stop();
}
