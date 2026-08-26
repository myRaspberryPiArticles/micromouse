//from back of cell the readings are as follows:

//right no wall is roughly 45 - 55
//front no wall is roughly 100 - 120
//left no wall is roughly 30 - 40

//right wall is roughly 95 - 110 (threshold 75)
//front wall is roughly 150 - 190 (threshold 140)
//left wall is roughly 90 - 100 (threshold 75)

void initFinal() {
  
}

//uint8_t turn_counts = 0;

void runFinal() {
  // gap on left, so turn left
  Serial.print("LEFT SENSOR IS AT ");
  Serial.print(leftSensorValue);
  Serial.print(" , threshold is 50, descision: ");
  bool hmm = leftSensorValue < 50;
  Serial.print(hmm);
  Serial.println();
  
  if (leftSensorValue < 50) {
    printSensors();
    Serial1.println("gap on left");
    test_left();
    printSensors();
    delay(100);
    one_cell_forward();
    delay(100);
    printSensors();
  }
    
  // wall in front, so turn right
   else if (frontSensorValue >= FRONT_THRESHOLD) {
    printSensors();
    Serial1.println("wall in front");
    test_right();
    delay(100);
    printSensors();
    //turn_counts += 1;

    /*if (turn_counts == 2) {
      backup();
      turn_counts = 0;
    }*/
   }

  // else go forward
  else {
    Serial1.println("going forward");
    one_cell_forward();
    delay(100);
    printSensors();
  }

  delay(500);
     
}
