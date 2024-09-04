

/**
* Bluetooth controlled Tank vehicle
*
*
*
*
*
**/

void setup() {
  // Configure console
  Serial.begin(9600);
  Serial.println("Tank initializing...");

  // Setup peripheries
  LED_setup();
  SONAR_setup();


  // Initialize bluetooth
}

void loop() {
  Serial.print("Distance: ");
  Serial.println(SONAR_readDistance());


  delay(500);
  LED_blinkStatusLed();
}