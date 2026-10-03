// ============================================================
//  Steering Servo Control
//    setup_servo() — attach steering servo and park at home
//    turn_left()   — sweep steering left, reset
//    turn_right()  — sweep steering right, reset
// ============================================================

#include <Servo.h>

Servo servo; // GPIO 2 (J5 — standard servo)

const int STEERING_HOME = 90; // Zero position for Steering Servo (GPIO 2)

void setup_servo() {
  servo.attach(2, 500, 2500);
  servo.write(STEERING_HOME);
  delay(300); // Allow physical movement to settle
}

// Set steering to startValue, sweep steering, then reset to home position
void turnSteering(int startValue, int step, int steps) {
  servo.write(startValue);
  delay(50);

  actuatorDrivePulses(-16000);
  delay(100);

  int value = startValue;
  for (int i = 0; i < steps; i++) {
    servo.write(value);
    value += step;
    delay(5);
  }

  actuatorDrivePulses(16000);  
  delay(100);
  
  servo.write(STEERING_HOME);
  delay(50);
}

void turn_left()  { turnSteering(30,  +1, 76); } // 30 -> 117
void turn_right() { turnSteering(150, -1, 80); } // 150 -> 65
