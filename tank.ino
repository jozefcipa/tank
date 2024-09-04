

/**
* Bluetooth controlled Tank vehicle
*
*
*
*
*
**/

void setup() {
  Serial.begin(9600);

  Serial.println("Tank initializing...");
  SONAR_setup();
}

void loop() {
  Serial.print("Distance: ");
  Serial.println(SONAR_readDistance());
  delay(500);
}