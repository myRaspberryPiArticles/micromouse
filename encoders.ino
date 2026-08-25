// Gemini Encoders
// Step 1. `initEncoders();` which sets up the pins and attaches interrupts
// The, use variables `leftEncoderValue` and `rightEncoderValue` to access
// Use `printEncoders();` to output the values in format L R
// Includes function `calculateDistancePulses(mm)` to calculate how many pulses to travel
// and `calculateAnglePulses(deg)` for angle
// and `pulsesToDistance(pulses)` to reverse this
// and `resetEncoders()` to set both values to 0

#define ENCODER_A 22
#define ENCODER_B 5

#define PULSES_PER_MM 21025

void initEncoders() {
  // Set pin mode
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderISR_B, CHANGE);

}

//int encoderValue = 0;

void encoderISR_A() {
  // When A changes: if A != B, we moved Forward (++)
  if (digitalRead(ENCODER_A) != digitalRead(ENCODER_B)) {
    encoderValue--;
  } else {
    encoderValue++;
  }
}

void encoderISR_B() {
  // When B changes: if A == B, we moved Forward (++)
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    encoderValue--;
  } else {
    encoderValue++;
  }
}

void one_cell_forward() {
  encoderValue = 0;
  while (encoderValue < PULSES_PER_MM) {
    setMotors(255);
    Serial1.println(encoderValue);
  }
  stop();
}
