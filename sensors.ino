// ============================================================
//  Reflective wall sensors (emitter + phototransistor pairs)
//    initSensors()  — set up pins
//    updateSensors() — call continuously from core 1 (loop1)
//    printSensors() — prints "R F L" over Serial1
//
//  Reading = analog(LED on) - analog(LED off), floored at 0.
//  Typical readings (from the back of a cell):
//    right: no wall ≈ 45-55,   wall ≈ 95-110
//    front: no wall ≈ 100-120, wall ≈ 150-190
//    left:  no wall ≈ 30-40,   wall ≈ 90-100
//  Detection thresholds are set in the main sketch.
// ============================================================

// Emitters
#define E_LEFT_RIGHT 15
#define E_FRONT      14

// Phototransistors
#define S_LEFT  26
#define S_FRONT 27
#define S_RIGHT 28

const uint8_t SETTLING_US = 75;  // wait after switching emitters on/off

void initSensors() {
  pinMode(E_LEFT_RIGHT, OUTPUT);
  pinMode(E_FRONT, OUTPUT);

  pinMode(S_LEFT,  INPUT);
  pinMode(S_FRONT, INPUT);
  pinMode(S_RIGHT, INPUT);
}

void updateSensors() {
  // --- FRONT SENSOR ---
  int frontUnlit = analogRead(S_FRONT);

  digitalWrite(E_FRONT, HIGH);
  delayMicroseconds(SETTLING_US);
  frontSensorValue = max(0, analogRead(S_FRONT) - frontUnlit);
  digitalWrite(E_FRONT, LOW);

  delayMicroseconds(SETTLING_US);

  // --- SIDE SENSORS (shared emitter) ---
  int leftUnlit  = analogRead(S_LEFT);
  int rightUnlit = analogRead(S_RIGHT);

  digitalWrite(E_LEFT_RIGHT, HIGH);
  delayMicroseconds(SETTLING_US);
  leftSensorValue  = max(0, analogRead(S_LEFT)  - leftUnlit);
  rightSensorValue = max(0, analogRead(S_RIGHT) - rightUnlit);
  digitalWrite(E_LEFT_RIGHT, LOW);

  delayMicroseconds(SETTLING_US);
}

void printSensors() {
  Serial1.print(leftSensorValue);
  Serial1.print(" ");
  Serial1.print(frontSensorValue);
  Serial1.print(" ");
  Serial1.print(rightSensorValue);
  Serial1.println();
}
