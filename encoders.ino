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

#define ACTUATOR_ENCODER_A 3
#define ACTUATOR_ENCODER_B 4

const uint32_t PULSES_PER_CELL     = 5075;                   // full cell
const long PULSES_TO_SENSE_POINT   = PULSES_PER_CELL * 0.6;  // 10938
const long PULSES_FROM_SENSE_POINT = PULSES_PER_CELL * 0.4;  // 7292
const long BACKUP_PULSES = 388; // or 777 for double of 388  // 7292

void initEncoders() {
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ACTUATOR_ENCODER_A, INPUT_PULLUP);
  pinMode(ACTUATOR_ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ACTUATOR_ENCODER_A), actuatorISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ACTUATOR_ENCODER_B), actuatorISR_B, CHANGE);
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

// --- ACTUATOR ---
void actuatorISR_A() {
  if (digitalRead(ACTUATOR_ENCODER_A) != digitalRead(ACTUATOR_ENCODER_B)) {
    actuatorValue++;
  } else {
    actuatorValue--;
  }
}

void actuatorISR_B() {
  if (digitalRead(ACTUATOR_ENCODER_A) == digitalRead(ACTUATOR_ENCODER_B)) {
    actuatorValue++;
  } else {
    actuatorValue--;
  }
}


// Drive until the encoder has counted `pulses` pulses.
// Positive = forward (counter climbs), negative = backward (counter falls).
void drivePulses(long pulses) {
  encoderValue = 0;
  unsigned long startTime = millis();
  const unsigned long TIMEOUT_MS = 5000; // 5-second safety timeout for wheels

  if (pulses >= 0) {
    while (encoderValue < pulses) {
      setMotors(255);
      
      // Safety escape if wheels are stuck or slipping
      if (millis() - startTime > TIMEOUT_MS) {
        break; 
      }
    }
    stop();
  } else {
    while (encoderValue > pulses) {
      setMotors(-255);
      
      // Safety escape if wheels are stuck or slipping
      if (millis() - startTime > TIMEOUT_MS) {
        break; 
      }
    }
    stop();
  }
}

void actuatorDrivePulses(long actuator_pulses) {
  actuatorValue = 0;
  unsigned long startTime = millis();
  const unsigned long TIMEOUT_MS = 6000; // 3-second safety timeout

  if (actuator_pulses >= 0) {
    while (actuatorValue < actuator_pulses) {
      setActuator(255);
      
      // Safety escape if it hits a physical end-stop or stalls
      if (millis() - startTime > TIMEOUT_MS) {
        break;
      }
    }
    actuator_stop();
  } else {
    while (actuatorValue > actuator_pulses) {
      setActuator(-255);
      
      // Safety escape if it hits a physical end-stop or stalls
      if (millis() - startTime > TIMEOUT_MS) {
        break;
      }
    }
    actuator_stop();
  }
}

void one_cell_forward()     { drivePulses(PULSES_PER_CELL); } // unchanged target
void first_sense_forward()  { drivePulses(PULSES_TO_SENSE_POINT); }
void second_sense_forward() { drivePulses(PULSES_FROM_SENSE_POINT); }

// Drive backwards BACKUP_PULSES, then stop.
void backup() {
  setMotors(-255);
  delay(1000);
  stop();
  drivePulses(BACKUP_PULSES);
  delay(50);
}
