void initButtons() {
  Serial1.begin(9600); // Using Serial1 for standard Pico hardware serial
  while (!Serial1);    // Wait for Serial Monitor to open
  
  // Initialize the button pin with the built-in pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
 
  Serial1.println("Button Test Initialized. Press the button!");
}

void buttons() {
  // Read the state of the button
  int buttonState = digitalRead(BUTTON_PIN);
  int button2State = digitalRead(BUTTON_2_PIN);
  int button3State = digitalRead(BUTTON_3_PIN);
  
  // Remember: In INPUT_PULLUP mode, LOW means PRESSED
  if (buttonState == LOW) {
    delay(200); // Simple debounce delay to prevent text flooding
    test_left();
    delay(200); // Simple debounce delay to prevent text flooding
  } else {
    // Optional: Uncomment the line below if you want to see the idle state
    // Serial1.println("Button is not pressed."); 
  }
    if (button2State == LOW) {
    delay(200); // Simple debounce delay to prevent text flooding
    test_right();
    delay(200); // Simple debounce delay to prevent text flooding
  } else {
    // Optional: Uncomment the line below if you want to see the idle state
    // Serial1.println("Button is not pressed."); 
  }
  if (button3State == LOW) {
    delay(200); // Simple debounce delay to prevent text flooding
    one_cell_forward();
    delay(300); // Simple debounce delay to prevent text flooding
    stop();
  } else {
    // Optional: Uncomment the line below if you want to see the idle state
    // Serial1.println("Button is not pressed."); 
  }
}
