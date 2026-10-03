bool left_then_forward = false;

void runFinal() {
  Serial1.println("new loop iteration");  
  printSensors();

  // Reverse if too close to front wall
  if (frontSensorValue >= 170) {
    delay(50);
    Serial1.println("too close to wall");  
    drivePulses(-700);
    delay(50);
  }
  
  // If wall on right and gap on left 
  if ((leftSensorValue < LEFT_THRESHOLD) && (rightSensorValue > RIGHT_THRESHOLD)) {
    Serial1.println("left turn (with backup)");
    
    turn_left();
    
    delay(50);
    
    backup();
    
    if (frontSensorValue >= FRONT_THRESHOLD) { // wall in front
        left_then_forward = false;
    } else {
        one_cell_forward();
        left_then_forward = true;
    }
  }
  
  // If gap on left and gap on right
  else if ((leftSensorValue < LEFT_THRESHOLD) && (rightSensorValue < RIGHT_THRESHOLD)) {
    Serial1.println("left turn (without backup)");
    
    turn_left();
    
    delay(100);

    if (frontSensorValue >= FRONT_THRESHOLD) { // wall in front
        left_then_forward = false;
    } else {
        one_cell_forward();
        left_then_forward = true;
    }
  }
  
  // If wall in front
  else if (frontSensorValue >= FRONT_THRESHOLD) {
    Serial1.println("right turn");
    turn_right();
    
    delay(50);
    
    backup();
  }

  else {
    if (left_then_forward == true) {
      Serial1.println("already went forward");
      left_then_forward = false;
    }

    else {
      // Go forward
      one_cell_forward();
      Serial1.println("One cell forward");
      left_then_forward = false;
    }
  }

  delay(50);

 }
