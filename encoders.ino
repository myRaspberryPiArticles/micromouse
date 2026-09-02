// ============================================================
//  Wheel encoders — both edges of both channels feed one shared
//  pulse counter, `encoderValue` (volatile long).
//
//    initEncoders()         — set up pins + interrupts
//    one_cell_forward()     — drive a full cell
//    first_sense_forward()  — drive to the sensing point (60% of a cell)
//    second_sense_forward() — drive to the cell end (remaining 40%)
//    backup()               — reverse kick, then drive forward again
// ============================================================

#define ENCODER_A 22
#define ENCODER_B 5

const uint32_t PULSES_PER_CELL = 18250;                       // full cell
const long PULSES_TO_SENSE_POINT   = PULSES_PER_CELL * 0.6;  // 10938
const long PULSES_FROM_SENSE_POINT = PULSES_PER_CELL * 0.4;  // 7292
const long BACKUP_PULSES           = 3169;                   // forward distance in backup()

void initEncoders() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), encoderISR_B, CHANGE);
}

// A changed: A != B means we rolled one way, A == B the other.
void encoderISR_A() {
  if (digitalRead(ENCODER_A) != digitalRead(ENCODER_B)) {
    encoderValue--;
  } else {
    encoderValue++;
  }
}

// B changed: opposite phase relationship to A.
void encoderISR_B() {
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    encoderValue--;
  } else {
    encoderValue++;
  }
}

// Drive forward at full speed until `targetPulses` have been counted.
void driveForward(long targetPulses) {
  encoderValue = 0;
  while (encoderValue < targetPulses) {
    setMotors(255);
  }
}

void one_cell_forward()     { driveForward(PULSES_PER_CELL); }
void first_sense_forward()  { driveForward(PULSES_TO_SENSE_POINT); }
void second_sense_forward() { driveForward(PULSES_FROM_SENSE_POINT); }

// Reverse pulse to break loose, then drive forward BACKUP_PULSES.
// (Despite the name, the net motion is forward — kept exactly as-is.)
void backup() {
  setMotors(-255);
  delay(100);
  encoderValue = 0;
  stop();

  while (encoderValue < BACKUP_PULSES) {
    setMotors(255);
  }
  stop();
}
