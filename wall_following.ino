//from back of cell the readings are as follows:

//right no wall is roughly 45 - 55
//front no wall is roughly 100 - 120
//left no wall is roughly 30 - 40

//right wall is roughly 95 - 110 (threshold 75)
//front wall is roughly 150 - 190 (threshold 140)
//left wall is roughly 90 - 100 (threshold 75) 

uint8_t leftSensorValueNEW = 0;
uint8_t frontSensorValueNEW = 0;
uint8_t rightSensorValueNEW = 0;
  
//uint8_t turn_counts = 0;

void runFinal() {
  // go half a cell forward
  half_cell_forward();

  // stop at the sensing point & take the value of left
  stop();
  delay(100);
  int uleftSensorValueNEW = leftSensorValue;

  half_cell_forward(); // go to middle of next cell

  // check if the value at the snesing point says there's a gap
  if (leftSensorValueNEW < LEFT_THRESHOLD) {
    // gap on left, so turn left
    Serial1.print("LEFT SENSOR IS AT ");
    Serial1.print(leftSensorValue);
    Serial1.print(" , threshold is ??, descision: ");
    bool hmm = leftSensorValue < LEFT_THRESHOLD;
    Serial1.print(hmm);
    Serial1.println();
  
    Serial1.println("gap on left");
    stop();
    delay(100);
  
    test_left();
    
    delay(200);
    one_cell_forward();
    delay(200);
    printSensors();
  }
    
  // wall in front, so turn right
   else if (frontSensorValue >= FRONT_THRESHOLD) {
    
    delay(200);
    stop();
    delay(200);
    
    printSensors();
    Serial1.println("wall in front");
    test_right();
    delay(200);
    printSensors();
    //turn_counts += 1;
   }

  else { // go to middle of the next cell because it's the way to go
    Serial1.println("going forward");
    one_cell_forward();
    delay(200);
    printSensors();
  }
  

  
    /*if (turn_counts == 2) {
      backup();
      turn_counts = 0;
    }*/
   // }

  delay(200);
  stop();
  delay(200);
}
