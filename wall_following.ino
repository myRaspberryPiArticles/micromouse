void initFinal() {
  
}

void runFinal() {
      
  while (true) {
  
      // 1. Check for DEAD END first (most specific condition)
      if (leftSensorValue >= 80 && frontSensorValue >= 8 && rightSensorValue >= 80) { 
          test_left();
          delay(100);
          test_left();
          delay(100);
      }
      // 2. Corner: Wall on left and front -> Turn Right
      else if (leftSensorValue >= 80 && frontSensorValue >=6) { 
          test_right();
          delay(100);
      }
      // 3. Gap: Space on left -> Turn Left
      else if (leftSensorValue <= 60) { 
          test_left();
          delay(100);
      }
  
      one_cell_forward();
      delay(100);
  }
     
}
