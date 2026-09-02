// ============================================================
//  Wall-following run logic (called from loop())
//    runFinal() — drive one cell at a time, deciding at the sensing
//    point whether to turn left, turn right, or keep going.
//  Thresholds (LEFT_/FRONT_/RIGHT_THRESHOLD) and the live sensor
//  values are defined in the main sketch.
// ============================================================

void runFinal() {
  first_sense_forward();  // drive to the sensing point

  // Stop at the sensing point and snapshot the side sensor values
  stop();
  delay(100);
  int leftAtSensePoint  = leftSensorValue;
  int rightAtSensePoint = rightSensorValue;

  second_sense_forward();

  // Gap on left AND wall on right -> turn left (with a backup)
  if ((leftAtSensePoint < LEFT_THRESHOLD) && (rightAtSensePoint > RIGHT_THRESHOLD)) {
    Serial1.println("gap on left");
    stop();
    delay(100);

    test_left();
    delay(200);
    //backup
    delay(200);
    one_cell_forward();
    delay(200);
    printSensors();
  }

  Serial1.print("LEFT SENSOR IS AT ");
  Serial1.print(leftSensorValue);
  Serial1.print(" , threshold is ??, descision: ");
  Serial1.print(leftSensorValue < LEFT_THRESHOLD);
  Serial1.println();

  // Gap on left and open on the right -> turn left
  if ((leftAtSensePoint < LEFT_THRESHOLD) && (rightAtSensePoint < RIGHT_THRESHOLD)) {
    Serial1.println("gap on left");
    stop();
    delay(100);

    test_left();
    delay(200);
    one_cell_forward();
    delay(200);
    printSensors();
  }
  else if (frontSensorValue >= FRONT_THRESHOLD) {
    // Wall in front -> turn right
    delay(200);
    stop();
    delay(200);

    printSensors();
    Serial1.println("wall in front");
    test_right();
    delay(200);
    //backup
    printSensors();
  }
  else {
    // Path clear ahead -> continue forward
    Serial1.println("going forward");
    one_cell_forward();
    delay(200);
    printSensors();
  }

  delay(200);
  stop();
  delay(200);
}
