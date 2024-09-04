/**
* Bluetooth controlled Tank vehicle
**/

#include <Wire.h>
#include "thermometer.h"

void setup() {
  // Configure console
  Serial.begin(9600);
  Serial.println("Tank initializing...");

  // Setup peripheries
  LED_setup();
  SONAR_setup();

  // Initialize I2C communication
  Wire.begin();
  COMPASS_setup();
  THERMOMETER_setup();

  // Initialize bluetooth at the end, when everything is ready
  BLUETOOTH_setup();

  Serial.println("Tank initialization is complete.");
}

void loop() {
  Serial.print("Distance: ");
  Serial.print(SONAR_readDistance());
  Serial.println("cm");
  Serial.print("Compass: ");
  Serial.print(COMPASS_read());
  Serial.println("°");
  Serial.print("Temperature: ");
  struct TemperatureHumidity temp;
  temp = THERMOMETER_read();
  Serial.print(temp.temperature);
  Serial.print("°C Humidity: ");
  Serial.print(temp.humidity);
  Serial.println("%");
  Serial.println("-----------------");

  String response = _BLUETOOTH_read();

  if (response != "") {
    Serial.println("Response from bluetooth");
    Serial.println(response);

    if (response.equals("on")) {
     LED_turnOnLights();
    } else if (response.equals("off")) {
      LED_turnOffLights();
    } else {
      Serial.println("Unknown command: " + response);
    }

    BLUETOOTH_send("OK");
  }

  delay(1000);
  LED_blinkStatusLed();
}