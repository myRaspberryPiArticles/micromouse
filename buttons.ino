// ============================================================
//  Push buttons (INPUT_PULLUP: LOW = pressed)
//    initButtons() — set up pins
//    buttons()     — poll and trigger the test actions
//  Pin numbers (BUTTON_PIN / _2 / _3) are defined in the main sketch.
// ============================================================

void initButtons() {
  pinMode(BUTTON_PIN,   INPUT_PULLUP); // 21  -> top left
  pinMode(BUTTON_2_PIN, INPUT_PULLUP); // 10  -> top right
  pinMode(BUTTON_3_PIN, INPUT_PULLUP); // 8   -> bottom left
                                       // RST -> bottom right

  Serial1.println("Button Test Initialized. Press the button!");
}

void buttons() {
  // Button 1 — sweep steering left
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200);      // debounce
    turn_left();
    delay(200);      // debounce
  }

  // Button 2 — sweep steering right
  if (digitalRead(BUTTON_2_PIN) == LOW) {
    delay(200);
    turn_right();
    delay(200);
  }

  // Button 3 — drive one cell
  if (digitalRead(BUTTON_3_PIN) == LOW) {
    delay(200);
    one_cell_forward();
    delay(300);
    stop();
  }
}
