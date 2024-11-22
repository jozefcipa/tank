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
#include "motors/motors.h"

char *btMessage;

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

void handleMotors(char *cmdVal) {
  Serial.print("[Motors]: Turning motors: ");
  Serial.println(cmdVal);

  // TODO: implement motors

  // if (strlen(cmdVal) != 6) { // e.g. LF:RF\0
  //   Serial.print("[motors]: Unknown command: ");
  //   Serial.println(cmdVal);
  //   return;
  // }

  // // move motors, cmdVal format is e.g. "LF:RF"
  // motors::move(cmdVal[0], cmdVal[1]);
  // motors::move(cmdVal[3], cmdVal[4]);
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

void loop() {
  led::blinkStatusLed();

  // We need to save the string message first, in order to keep the c_str() reference valid
  // See https://gcc.gnu.org/onlinedocs/gcc/Temporaries.html
  String message = bluetooth::read();
  btMessage = (char *) message.c_str();
  if (strcmp(btMessage, "") == 0) {
    delay(50);
    return;
  }

  // parse message
  Serial.print("[Bluetooth]: Received message: ");
  Serial.println(btMessage);
  tank::Command command = tank::parseMessage(btMessage);

  // handle motors
  if (command.motors != NULL) {
    handleMotors(command.motors);
  }

  // handle lights
  if (command.lights != NULL) {
    handleLEDLights(command.lights);
  }

  // handle sensors data
  if (command.sensors != NULL) {
    handleSensors(command.sensors);
  }
}
