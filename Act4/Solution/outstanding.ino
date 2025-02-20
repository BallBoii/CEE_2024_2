// --- Constants and Pin Definitions ---
enum class GameState {
    STATE_DISPLAY,
    STATE_INPUT,
    STATE_RESULT
  };
  GameState state = GameState::STATE_DISPLAY;
  
  const int BUTTON_A = 2; 
  const int BUTTON_B = 7;
  const int LED_RED  = 5; 
  const int LED_GREEN = 9; 
  const int LED_BLUE  = 6;
  
  // --- Game Variables ---
  char sequence[4];      // Stores the randomly generated sequence (e.g., 'A', 'B', 'A', 'B')
  char userInput[4];     // Stores the sequence entered by the user
  int displayIndex = 0;  // Index for displaying the sequence
  int inputIndex = 0;    // Index for recording user input
  bool win = false;      // Flag to record if the user entered the correct sequence
  
  // Timing variable for the DISPLAY phase
  unsigned long lastTime = 0;
  const unsigned long DISPLAY_INTERVAL = 1000; // Time (in ms) between flashes
  
  // Variables for button state change detection in the INPUT state
  // With INPUT_PULLUP, the buttons are HIGH when unpressed.
  int lastA = HIGH, lastB = HIGH;
  
  void setup() {
    Serial.begin(9600);
    
    // Initialize button pins as inputs with internal pull-ups.
    // Wire the buttons between the pin and ground.
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    
    // Initialize LED pins as outputs.
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    
    // Turn off all LEDs initially.
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    
    // Seed the random generator (using an unconnected analog pin for noise).
    randomSeed(analogRead(0));
    
    // Generate the first random sequence and prepare for display.
    generateSequence();
    state = GameState::STATE_DISPLAY;
    displayIndex = 0;
    inputIndex = 0;
    lastTime = millis();
    
    Serial.println("Game Started: Watch the sequence and then repeat it using the buttons.");
  }
  
  void loop() {
    unsigned long currentMillis = millis();
    
    switch(state) {
  
      case GameState::STATE_DISPLAY: {
        // Display the sequence one flash at a time.
        if (displayIndex < 4 && currentMillis - lastTime >= DISPLAY_INTERVAL) {
          if (sequence[displayIndex] == 'A') {
            // For 'A', flash the green LED.
            digitalWrite(LED_GREEN, HIGH);
            delay(300);
            digitalWrite(LED_GREEN, LOW);
          } else if (sequence[displayIndex] == 'B') {
            // For 'B', flash the red LED.
            digitalWrite(LED_RED, HIGH);
            delay(300);
            digitalWrite(LED_RED, LOW);
          }
          displayIndex++;
          lastTime = currentMillis;
        } 
        else if (displayIndex >= 4) {
          // After displaying the sequence, switch to INPUT state.
          delay(500); // Brief pause before input begins.
          state = GameState::STATE_INPUT;
          inputIndex = 0;
          // Read the current button states to avoid false triggers.
          lastA = digitalRead(BUTTON_A);
          lastB = digitalRead(BUTTON_B);
          Serial.println("Your turn! Repeat the sequence by pressing the buttons.");
        }
        break;
      }
  
      case GameState::STATE_INPUT: {
        // Read the pushbuttons and record user input (using edge detection).
        int curA = digitalRead(BUTTON_A);
        int curB = digitalRead(BUTTON_B);
        
        // Detect a falling edge for Button A (HIGH to LOW indicates a press).
        if (curA != lastA) {
          if (curA == LOW) {
            userInput[inputIndex] = 'A';
            inputIndex++;
            Serial.println("Input: A");
            delay(50); // Simple debounce delay.
          }
          lastA = curA;
        }
        
        // Detect a falling edge for Button B.
        if (curB != lastB) {
          if (curB == LOW) {
            userInput[inputIndex] = 'B';
            inputIndex++;
            Serial.println("Input: B");
            delay(50); // Debounce delay.
          }
          lastB = curB;
        }
        
        // Once 4 inputs are recorded, check the sequence.
        if (inputIndex >= 4) {
          win = true;
          for (int i = 0; i < 4; i++) {
            if (userInput[i] != sequence[i]) {
              win = false;
              break;
            }
          }
          state = GameState::STATE_RESULT;
        }
        break;
      }
  
      case GameState::STATE_RESULT: {
        // Show the outcome using LED animations.
        if (win) {
          Serial.println("Correct! You win!");
          // Winning pattern: Blink the blue LED several times.
          for (int i = 0; i < 5; i++) {
            digitalWrite(LED_BLUE, HIGH);
            delay(200);
            digitalWrite(LED_BLUE, LOW);
            delay(200);
          }
        } else {
          Serial.println("Incorrect! Try again!");
          // Losing pattern: Blink the red LED several times.
          for (int i = 0; i < 5; i++) {
            digitalWrite(LED_RED, HIGH);
            delay(200);
            digitalWrite(LED_RED, LOW);
            delay(200);
          }
        }
        
        // After displaying the result, start a new round:
        generateSequence();  // Create a new random sequence.
        displayIndex = 0;
        inputIndex = 0;
        lastTime = millis();
        state = GameState::STATE_DISPLAY;
        delay(500);
        break;
      }
    }
  }
  
  // Function to generate a new random sequence of 'A's and 'B's.
  void generateSequence() {
    for (int i = 0; i < 4; i++) {
      int r = random(0, 2); // Generates 0 or 1.
      sequence[i] = (r == 0) ? 'A' : 'B';
    }
    
    // For debugging: print the new sequence to the Serial Monitor.
    Serial.print("New sequence: ");
    for (int i = 0; i < 4; i++) {
      Serial.print(sequence[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
  