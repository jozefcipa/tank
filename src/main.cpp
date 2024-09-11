/**
* Bluetooth controlled Tank vehicle
**/
#include <Arduino.h>
#include <Wire.h>
#include<string.h>
#include "leds/leds.h"
#include "sonar/sonar.h"
#include "compass/compass.h"
#include "thermometer/thermometer.h"
#include "bluetooth/bluetooth.h"
#include "tank/tank.h"

void setup() {
  // Configure console
  Serial.begin(9600);
  Serial.println("Tank initializing...");

  // Setup peripheries
  led::setup();
  sonar::setup();

  // Initialize I2C communication
  Wire.begin();
  compass::setup();
  temp::setup();

  // Initialize bluetooth at the end, when everything is ready
  bluetooth::setup();

  Serial.println("Tank initialization is complete.");
}

void handleLEDLights(char *cmdVal) {
  if (strcmp(cmdVal, "ON") == 0) {
    Serial.print("[Lights]: Turning LEDs ON");
    led::turnOnLights();
    Serial.print("[Lights]: Turning LEDs OFF");
  } else if (strcmp(cmdVal, "OFF") == 0) {
    led::turnOffLights();
  } else {
    Serial.print("[Lights]: Unknown command: ");
    Serial.println(cmdVal);
  }
}

void handleSensors(char *cmdVal) {
  if (strcmp(cmdVal, "READ") == 0) {
    Serial.print("[Sensors]: Reading sensor values");

    int sonarDistance = sonar::readDistance();
    int compassPosition = compass::read();
    struct temp::TemperatureHumidity tempHumidity = temp::read();

    char *sensorValues;
    sprintf(sensorValues, "sensors=sonar:%d|compass:%d|temperature:%.2f|humidity:%.2f;lights=%s", sonarDistance, compassPosition, tempHumidity.temperature, tempHumidity.humidity, led::lightsTurnedOn ? "ON" : "OFF");

    Serial.print("[Sensors]: Sending sensor values: ");
    Serial.println(sensorValues);
    bluetooth::send(sensorValues);
  } else {
    Serial.print("[Sensors]: Unknown command: ");
    Serial.println(cmdVal);
  }
}

void loop() {
  led::blinkStatusLed();

  char *message = bluetooth::read();
  if (strcmp(message, "") == 0) {
    delay(1000); // TODO: decrease
    return;
  }

  Serial.println("[Bluetooth]: Received message: ");
  Serial.println(message);

  tank::Command command = tank::parseMessage(message);

  // handle lights
  if (strcmp(command.lights, "") != 0) {
    handleLEDLights(command.lights);
  }

  // handle sensors data
  if (strcmp(command.sensors, "") != 0) {
    handleSensors(command.sensors);
  }

  // TODO handle motors
}
