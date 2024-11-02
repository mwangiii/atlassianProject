const int GAS_PIN = 4;         // MQ2 sensor connected to J4 (GPIO 4)
const int TONE_PIN = 12;       // Buzzer connected to J12 (GPIO 12)

// RGB LED pins connected to J13
const int LED_RED = 13;        
const int LED_GREEN = 14;
const int LED_BLUE = 15;

// PWM channel for tone
const int TONE_PWM_CHANNEL = 0;

void setup() {
  Serial.begin(115200);
  
  // Attach buzzer to PWM channel
  ledcAttachPin(TONE_PIN, TONE_PWM_CHANNEL);
  
  // Configure pins
  pinMode(GAS_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void loop() {
  int gasLevel = analogRead(GAS_PIN);  // Read gas level from MQ2 sensor

  Serial.print("Gas Level: ");
  Serial.print(gasLevel);
  Serial.print("\t");

  if (gasLevel > 1000) {  // Threshold for gas detection
    Serial.println("Gas Detected!");
    
    // Turn on RED LED for gas alert
    digitalWrite(LED_RED, HIGH);  
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    
    // Play tone on buzzer
    ledcWriteTone(TONE_PWM_CHANNEL, 1000); // 1 kHz tone
    delay(1000);  // Keep alert for 1 second
    
    // Turn off the LED and buzzer
    digitalWrite(LED_RED, LOW);
    ledcWriteTone(TONE_PWM_CHANNEL, 0); // Stop tone
  }
  else {
    Serial.println("No Gas Detected");

    // Turn on GREEN LED to indicate normal status
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
  
  delay(100);  // Short delay before the next reading
}
