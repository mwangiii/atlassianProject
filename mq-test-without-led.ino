const int GAS_PIN = 4;         // MQ2 sensor connected to GPIO 4 (J4)
const int TONE_PIN = 12;       // Buzzer connected to GPIO 12 (J12)

// The ESP32 has 16 channels which can generate 16 independent waveforms
// We'll use PWM channel 0 here for the buzzer
const int TONE_PWM_CHANNEL = 0;

void setup() {
  Serial.begin(115200);

  // Attach the buzzer to the PWM channel
  ledcAttachPin(TONE_PIN, TONE_PWM_CHANNEL);

  // Set up the MQ2 sensor pin
  pinMode(GAS_PIN, INPUT);
}

void loop() {
  // Read the gas level from the MQ2 sensor
  int gasLevel = analogRead(GAS_PIN);

  // Display the gas level on the Serial Monitor
  Serial.print("Gas Level: ");
  Serial.print(gasLevel);
  Serial.print("\t");

  // Check if gas level is above the threshold
  if (gasLevel > 1000) {
    Serial.println("Gas Detected");
    ledcWriteTone(TONE_PWM_CHANNEL, 262);   // Play C4 (262 Hz) on the buzzer
    delay(1000);                            // Wait for 1 second
    ledcWriteTone(TONE_PWM_CHANNEL, 0);     // Stop the tone
  } else {
    Serial.println("No Gas Detected");
  }

  delay(100);  // Check every 100 ms
}
