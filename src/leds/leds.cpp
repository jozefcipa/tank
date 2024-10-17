#include <Arduino.h>
#include <stdbool.h>

namespace led {
  const int STATUS_LED = 9;
  const int FRONT_LED = 40;
  const int REAR_LED = 41;
  bool lightsTurnedOn = false;

  void turnOnLights() {
    digitalWrite(FRONT_LED, HIGH);
    digitalWrite(REAR_LED, HIGH);
    lightsTurnedOn = true;
  }

  void turnOffLights() {
    digitalWrite(FRONT_LED, LOW);
    digitalWrite(REAR_LED, LOW);
    lightsTurnedOn = false;
  }

  void blinkStatusLed() {
    digitalWrite(STATUS_LED, HIGH);
    delay(200);
    digitalWrite(STATUS_LED, LOW);
  }

  void setup() {
    pinMode(STATUS_LED, OUTPUT);
    pinMode(FRONT_LED, OUTPUT);
    pinMode(REAR_LED, OUTPUT);

    turnOnLights();
    delay(100);
    turnOffLights();
    delay(100);
    turnOnLights();
    delay(300);
    turnOffLights();

    Serial.println("LEDs configured.");
  }
}