// ============================================================
//  Wheel encoders — both edges of both channels feed one shared
//  pulse counter, `encoderValue` (volatile long).
//  Forward motion counts UP; reverse motion counts DOWN.
//
//    initEncoders()         — set up pins + interrupts
//    one_cell_forward()     — drive a full cell
//    first_sense_forward()  — drive to the sensing point (60% of a cell)
//    second_sense_forward() — drive to the cell end (remaining 40%)
//    backup()               — drive BACKUP_PULSES backwards
// ============================================================

#define ENCODER_A 22
#define ENCODER_B 5

const uint32_t PULSES_PER_CELL = 18230;                      // full cell
const long PULSES_TO_SENSE_POINT   = PULSES_PER_CELL * 0.6;  // 10938
const long PULSES_FROM_SENSE_POINT = PULSES_PER_CELL * 0.4;  // 7292
const long BACKUP_PULSES           = 3169;                   // backup distance

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

// Drive until the encoder has counted `pulses` pulses.
// Positive = forward (counter climbs), negative = backward (counter falls).
void drivePulses(long pulses) {
  encoderValue = 0;

  if (pulses >= 0) {
    while (encoderValue < pulses) {
      setMotors(255);
    }
    stop();
  } else {
    while (encoderValue > pulses) {
      setMotors(-255);
    }
    stop();
  }
}

void one_cell_forward()     { drivePulses(PULSES_PER_CELL); } // unchanged target
void first_sense_forward()  { drivePulses(PULSES_TO_SENSE_POINT); }
void second_sense_forward() { drivePulses(PULSES_FROM_SENSE_POINT); }

// Drive backwards BACKUP_PULSES, then stop.
void backup() {
  drivePulses(-BACKUP_PULSES);
  stop();
}
