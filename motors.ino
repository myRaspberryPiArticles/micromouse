// ============================================================
//  Motor driver (DRV8833) — single drive motor
//    initMotors()     — set up pins + wake the driver
//    setMotors(speed) — -255..255; the sign picks the direction
//    stop()           — both PWM outputs to 0
//
//  PWM scheme: the "off" pin runs at 255 - |speed|, so a speed of
//  255 gives a fully-on duty cycle.
// ============================================================

#define M_FORWARD   17
#define M_BACKWARD  16
#define A_FORWARD   19
#define A_BACKWARD  18
#define SLP         20

const int MAX_SPEED = 255;

void initMotors() {
  pinMode(M_FORWARD, OUTPUT);
  pinMode(M_BACKWARD, OUTPUT);
  pinMode(A_FORWARD, OUTPUT);
  pinMode(A_BACKWARD, OUTPUT);
  pinMode(SLP, OUTPUT);

  digitalWrite(SLP, HIGH);  // wake up the DRV8833
}

void setMotors(int motor) {
  int absMotor = abs(motor);

  if (motor >= 0) {
    analogWrite(M_FORWARD,  MAX_SPEED);
    analogWrite(M_BACKWARD, MAX_SPEED - absMotor);
  } else {
    analogWrite(M_FORWARD,  MAX_SPEED - absMotor);
    analogWrite(M_BACKWARD, MAX_SPEED);
  }
}

void setActuator(int actuator) {
  int absActuator = abs(actuator);

  if (actuator >= 0) {
    analogWrite(A_FORWARD,  MAX_SPEED);
    analogWrite(A_BACKWARD, MAX_SPEED - absActuator);
  } else {
    analogWrite(A_FORWARD,  MAX_SPEED - absActuator);
    analogWrite(A_BACKWARD, MAX_SPEED);
  }
}

void stop() {
  analogWrite(M_FORWARD,  0);
  analogWrite(M_BACKWARD, 0);
}

void actuator_stop() {
  analogWrite(A_FORWARD,  0);
  analogWrite(A_BACKWARD, 0);
}
