// Docs
// https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

#define SONAR_TRIGGER_PIN 47
#define SONAR_ECHO_PIN 46

void SONAR_setup() {
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
  
  Serial.println("SONAR configured.");
}

int _SONAR_readValue() {
  // Clears the trigger pin
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  // Sets the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(SONAR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIGGER_PIN, LOW);

  // Reads the echo pin, returns the sound wave travel time in microseconds
  int duration = pulseIn(SONAR_ECHO_PIN, HIGH);

  // Calculate and return the distance
  return duration * 0.034 / 2;
}

int SONAR_readDistance() {
  int trials = 3;
  int sumDistance = 0;

  // For the better accuracy, measure the distance 3 times and return its average
  for (int i = 0; i < trials; i++) {
    sumDistance += _SONAR_readValue();
    delay(10);
  }

  return sumDistance / trials;
}