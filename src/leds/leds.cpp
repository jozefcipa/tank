#include <Arduino.h>

// LED pins
#define STATUS_LED 2
#define FRONT_LED 3
#define REAR_LED 4

bool LIGHTS_TURNED_ON = false;

void LED_turnOnLights() {
  digitalWrite(FRONT_LED, HIGH);
  digitalWrite(REAR_LED, HIGH);
  LIGHTS_TURNED_ON = true;
}

void LED_turnOffLights() {
  digitalWrite(FRONT_LED, LOW);
  digitalWrite(REAR_LED, LOW);
  LIGHTS_TURNED_ON = false;
}

void LED_blinkStatusLed() {
  digitalWrite(STATUS_LED, HIGH);
  delay(200);
  digitalWrite(STATUS_LED, LOW);
}

void LED_setup() {
  pinMode(STATUS_LED, OUTPUT);
  pinMode(FRONT_LED, OUTPUT);
  pinMode(REAR_LED, OUTPUT);

  LED_turnOnLights();
  delay(100);
  LED_turnOffLights();
  delay(100);
  LED_turnOnLights();
  delay(300);
  LED_turnOffLights();

  Serial.println("LEDs configured.");
}
