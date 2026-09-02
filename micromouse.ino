// ============================================================
//  Micromouse — main sketch (Raspberry Pi Pico, dual-core)
//    Core 0 (setup/loop)   : motors, servos, maze logic, serial
//    Core 1 (setup1/loop1) : sensor + MPU updates
// ============================================================

// --- Wall-detection thresholds (raw sensor ranges: see sensors.ino) ---
const uint8_t LEFT_THRESHOLD  = 100;
const uint8_t FRONT_THRESHOLD = 11;
const uint8_t RIGHT_THRESHOLD = 100;

// --- Live sensor readings (updated on core 1 by updateSensors()) ---
volatile int leftSensorValue  = 0;
volatile int frontSensorValue = 0;
volatile int rightSensorValue = 0;

// --- Wheel encoder pulse count (updated by ISRs in encoders.ino) ---
volatile long encoderValue = 0;

// --- Gyro headings (updated by updateMpu() in gyro.ino) ---
volatile float heading       = 0.0; // re-zeroed for each turn
volatile float globalHeading = 0.0; // never reset (debugging only)

// --- Button pins (used by buttons.ino) ---
const int BUTTON_PIN   = 21;
const int BUTTON_2_PIN = 10;
const int BUTTON_3_PIN = 8;

uint8_t mode = 0;

void setup() {
  Serial1.begin(9600);
  
  initButtons();
  initMpu();
  resetHeading();
  setup_servo();
  initMotors();
  initEncoders();

  delay(2000);

  Serial1.println("------micromouse------");
  Serial1.println();
  
  while (mode == 0) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      mode = 1; // button 1
    }
    else if (digitalRead(BUTTON_2_PIN) == LOW) {
      mode = 2; // button 2
    }
    else if (digitalRead(BUTTON_3_PIN) == LOW) {
      mode = 3; // button 3
    }
    
  }

  
}

void loop() {
  if (mode == 1) { printSensors(); buttons(); }
  else if (mode == 2) { runFinal(); }
  else if (mode == 3) { backup(); }
}

// --- Core 1: sensors & MPU ---

void setup1() {
  initSensors();
}

void loop1() {
  updateSensors();
}
