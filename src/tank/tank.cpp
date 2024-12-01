#include <Arduino.h>
#include <string.h>
#include <Wire.h>

#include "tank.h"
#include "motors/motors.h"
#include "bluetooth/bluetooth.h"
#include "leds/leds.h"
#include "sonar/sonar.h"
#include "thermometer/thermometer.h"
#include "compass/compass.h"

namespace tank {
  // For how long should the motors spin before stopping if no new command arrived
  const int MOTORS_COMMAND_TIMEOUT = 350; // ms
  unsigned long lastMotorsCommandTime = 0;
  boolean motorsRunning = false;

  struct Command parseMessage(char *msgStr) {
    Command command = {};

    // Split by ';' to get commands for individual peripheries
    char *peripheryCmd = strtok(msgStr, ";");

    while (peripheryCmd != NULL) {
      // Split by '=' to separate key and value
      char *key = strtok(peripheryCmd, "=");
      char *value = strtok(NULL, "=");

      // Compare the key and assign the value to the correct field
      if (strcmp(key, "lights") == 0) {
        command.lights = value;
      } else if (strcmp(key, "sensors") == 0) {
        command.sensors = value;
      } else if (strcmp(key, "motors") == 0) {
        command.motors = value;
      } else {
        Serial.print("[WARN]: Unknown key-value pair: ");
        Serial.print(key);
        Serial.print("=");
        Serial.println(value);
      }

      // Get the next key-value pair
      peripheryCmd = strtok(NULL, ";");
    }

    return command;
  }

  void setup() {
    // Setup peripheries
    led::setup();
    sonar::setup();

    // Initialize I2C communication
    Wire.begin();
    compass::setup();
    temp::setup();

    // Initialize bluetooth at the end, when everything is ready
    bluetooth::setup();
  }

  void handleMotors(char *cmdVal) {
    Serial.print("[Motors]: Spinning motors: ");
    Serial.println(cmdVal);

    if (strlen(cmdVal) != 5) { // e.g. LF:RF
      Serial.print("[Motors]: Unknown command: ");
      Serial.println(cmdVal);
      Serial.println(strlen(cmdVal));
      return;
    }

    // move motors, cmdVal format is e.g. "LF:RF"
    motors::drive(cmdVal[0], cmdVal[1], cmdVal[3], cmdVal[4]);
    motorsRunning = true;

    // reset timer
    lastMotorsCommandTime = millis();
  }

  void handleLEDLights(char *cmdVal) {
    if (strcmp(cmdVal, "ON") == 0) {
      Serial.println("[Lights]: Turning LEDs ON");
      led::turnOnLights();
    } else if (strcmp(cmdVal, "OFF") == 0) {
      Serial.println("[Lights]: Turning LEDs OFF");
      led::turnOffLights();
    } else {
      Serial.print("[Lights]: Unknown command: ");
      Serial.println(cmdVal);
    }
  }

  void handleSensors(char *cmdVal) {
    if (strcmp(cmdVal, "READ") == 0) {
      Serial.println("[Sensors]: Reading sensor values");

      int sonarDistance = sonar::readDistance();
      int compassPosition = compass::read();
      struct temp::TemperatureHumidity tempHumidity = temp::read();

      // sprintf() function in Arduino's AVR-based environment doesn't support floating-point formatting (%f),
      // that's why we need to cast those numbers to strings first
      char temperature[7]; // allow 7 characters: "100.00\0"
      char humidity[7];
      dtostrf(tempHumidity.temperature, 6, 2, temperature);
      dtostrf(tempHumidity.humidity, 6, 2, humidity);

      char sensorValues[100];
      sprintf(
        sensorValues,
        "sensors=sonar:%d|compass:%d|temperature:%s|humidity:%s;lights=%s\n",
        sonarDistance,
        compassPosition,
        temperature,
        humidity,
        led::lightsTurnedOn ? "ON" : "OFF"
      );
      
      Serial.print("[Sensors]: Sending sensor values: ");
      Serial.println(sensorValues);
      bluetooth::send(sensorValues);
    } else {
      Serial.print("[Sensors]: Unknown command: ");
      Serial.println(cmdVal);
    }
  }

  boolean shouldStopMotors() {
    // if we haven't received a new motor command for "MOTORS_COMMAND_TIMEOUT" ms motors should be stopped
    return (millis() - lastMotorsCommandTime) > MOTORS_COMMAND_TIMEOUT && motorsRunning;
  }

  void stopMotors() {
    Serial.print("[Tank]: Stopping motors as no new command received for ");
    Serial.print(MOTORS_COMMAND_TIMEOUT);
    Serial.println("ms");

    motors::stop('R');
    motors::stop('L');
    motorsRunning = false;
  }
}