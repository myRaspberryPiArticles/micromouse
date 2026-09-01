#include <Servo.h>

// Using GPIO 2 (J5 - Standard Servo)
Servo actuator;
Servo actuator2;
Servo servo;


void setup_servo() {
  actuator.attach(4);
  actuator2.attach(3);
  servo.attach(2, 500, 2500);
  //resetHeadingVariable(); // Reset heading to 0.0
  actuator.write(20);  // Note: 180 is the true physical maximum for standard servos
  actuator2.write(20); 
  servo.write(90);      // Snap back to straight center

}

void test_left() {
  int left_value = 30;   // Start at center home position (95)
  //resetHeadingVariable();*/ // Reset heading to 0.0
  servo.write(left_value);  
  delay(500);
  actuator.write(190); 
  actuator2.write(190); 
  delay(500);

  // 1. REVERSED DIRECTION: 
  // Loop while heading is GREATER than -83.3, and decrement right_value down toward 5
  //while (heading >= -90 && right_value > 5) { 
  //  updateMpu(); 
  int i;  
  //  right_value -= 1;          // 2. Decrementing turns the servo the opposite way
  for (i=1; i<=85; i++) {
    servo.write(left_value);
    left_value += 1;
    delay(10);
  }
  
  //}
  // Cleanup code
  actuator.write(20);  
  actuator2.write(20); 
  delay(300);
  servo.write(90);      // Snap back to straight center
  delay(300);
}

//_____________________________\\

void test_right() {
  int right_value = 150;   // Start at center home position (95)
  //resetHeadingVariable(); // Reset heading to 0.0
  servo.write(right_value);  
  delay(500);
  actuator.write(190); 
  actuator2.write(190); 
  delay(500);

  // 1. REVERSED DIRECTION: 
  // Loop while heading is GREATER than -83.3, and decrement right_value down toward 5
  //while (heading >= -90 && right_value > 5) { 
  //  updateMpu(); 
  int i;  
  //  right_value -= 1;          // 2. Decrementing turns the servo the opposite way
  for (i=1; i<=81; i++) {
    servo.write(right_value);
    right_value -= 1;
    delay(10);
  }
  //}
  // Cleanup code
  actuator.write(20);  
  actuator2.write(20); 
  delay(300);
  servo.write(90);      // Snap back to straight center
  delay(300);
}
