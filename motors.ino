// Gemini Motors Abstractor
// Step 1. `initMotors();` which sets up the pins and enables the driver
// The, use `setMotors(left, right);` with speeds up to 256
// Use `stop();` to stop

// Motor Pins
#define M_FORWARD   17
#define M_BACKWARD   16
#define SLP    20

void initMotors() {
  pinMode(M_FORWARD, OUTPUT);
  pinMode(M_BACKWARD, OUTPUT);

  pinMode(SLP, OUTPUT);

  // enable DRV8833
  digitalWrite(SLP, HIGH);
}

void setMotors(int motor) {
  int MAX_SPEED = 255;

  int absMotor = abs(motor);

  // IF positive number, Set the forward speeds to max, and the reverse speed to max - target
  // IF negative number, Set the backward speeds to max, and the forward speed to max - target

  if (motor >= 0) {
    analogWrite(M_FORWARD, MAX_SPEED);
    analogWrite(M_BACKWARD, MAX_SPEED - absMotor);
  } 
  else {
    analogWrite(M_FORWARD, MAX_SPEED - absMotor);
    analogWrite(M_BACKWARD, MAX_SPEED);
  }

}

void stop() {
  analogWrite(M_FORWARD, 0);
  analogWrite(M_BACKWARD, 0);
}
