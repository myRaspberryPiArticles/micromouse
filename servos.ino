// ============================================================
//  Steering servo + two actuators
//    setup_servo() — attach everything and park at home
//    test_left()   — fire actuators, sweep steering left, reset
//    test_right()  — fire actuators, sweep steering right, reset
// ============================================================

#include <Servo.h>

Servo actuator;   // GPIO 4
Servo actuator2;  // GPIO 3
Servo servo;      // GPIO 2 (J5 — standard servo)

const int ACTUATOR_HOME = 20;
const int ACTUATOR_FIRE = 190;  // deliberately past the usual 180 limit
const int STEERING_HOME = 90;

void setup_servo() {
  actuator.attach(4);
  actuator2.attach(3);
  servo.attach(2, 500, 2500);

  actuator.write(ACTUATOR_HOME);
  actuator2.write(ACTUATOR_HOME);
  servo.write(STEERING_HOME);
}

// Point at `startValue`, fire the actuators, sweep the steering servo
// `steps` times by `step` per move (10 ms per move), then reset.
void turnSteering(int startValue, int step, int steps) {
  servo.write(startValue);
  delay(500);

  actuator.write(ACTUATOR_FIRE);
  actuator2.write(ACTUATOR_FIRE);
  delay(500);

  int value = startValue;
  for (int i = 0; i < steps; i++) {
    servo.write(value);
    value += step;
    delay(10);
  }

  actuator.write(ACTUATOR_HOME);
  actuator2.write(ACTUATOR_HOME);
  delay(300);
  servo.write(STEERING_HOME);
  delay(300);
}

void test_left()  { turnSteering(30,  +1, 85); }  // 30 -> 114
void test_right() { turnSteering(150, -1, 81); } // 150 -> 70
