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

void handleLEDLights(char *cmdVal) {
  if (strcmp(cmdVal, "ON") == 0) {
    Serial.print("[Lights]: Turning LEDs ON");
    LED_turnOnLights();
    Serial.print("[Lights]: Turning LEDs OFF");
  } else if (strcmp(cmdVal, "OFF") == 0) {
    LED_turnOffLights();
  } else {
    Serial.print("[Lights]: Unknown command: ");
    Serial.println(cmdVal);
  }
}

void handleSensors(char *cmdVal) {
  if (strcmp(cmdVal, "READ") == 0) {
    Serial.print("[Sensors]: Reading sensor values");

    int distance = SONAR_readDistance();
    int compass = COMPASS_read();
    struct TemperatureHumidity temp = THERMOMETER_read();

    char *sensorValues;
    sprintf(sensorValues, "sensors=sonar:%d|compass:%d|temperature:%.2f|humidity:%.2f|lights:%s", distance, compass, temp.temperature, temp.humidity, LIGHTS_TURNED_ON ? "ON" : "OFF");

    Serial.print("[Sensors]: Sending sensor values: ");
    Serial.println(sensorValues);
    BLUETOOTH_send(sensorValues);
  } else {
    Serial.print("[Sensors]: Unknown command: ");
    Serial.println(cmdVal);
  }
}

void loop() {
  LED_blinkStatusLed();

  char *message = BLUETOOTH_read();
  if (strcmp(message, "") == 0) {
    delay(1000); // TODO: decrease
    return;
  }

  Serial.println("[Bluetooth]: Received message: ");
  Serial.println(message);

  TankCommand command = TANK_parseMessage(message);

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
