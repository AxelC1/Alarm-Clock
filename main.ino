// Constants
const int LED_PIN = 13;
const int BUTTON_PIN = 2;

// Setup function to initialize the Arduino environment
void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

// Main loop of the program
void loop() {
    if (digitalRead(BUTTON_PIN) == HIGH) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}