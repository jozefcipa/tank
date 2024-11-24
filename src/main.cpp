/**
* Bluetooth controlled Tank vehicle
**/
#include <Arduino.h>
#include <Wire.h>
#include <string.h>
#include "leds/leds.h"
#include "bluetooth/bluetooth.h"
#include "tank/tank.h"

char *bluetoothMessage;

void setup() {
  // Configure console
  Serial.begin(9600);
  Serial.println("Tank initializing...");
  tank::setup();
  Serial.println("Tank initialization is complete.");
}

void loop() {
  led::blinkStatusLed();

  // We need to save the string message first, in order to keep the c_str() reference valid
  // See https://gcc.gnu.org/onlinedocs/gcc/Temporaries.html
  String message = bluetooth::read();
  bluetoothMessage = (char *) message.c_str();
  if (strcmp(bluetoothMessage, "") == 0) {
    if (tank::shouldStopMotors()) {
      tank::stopMotors();
    }

    delay(50);
    return;
  }

  // Parse bluetooth message
  Serial.print("[Bluetooth]: Received message: ");
  Serial.println(bluetoothMessage);
  tank::Command command = tank::parseMessage(bluetoothMessage);

  // Handle motors
  if (command.motors != NULL) {
    tank::handleMotors(command.motors);
  }

  // Handle lights
  if (command.lights != NULL) {
    tank::handleLEDLights(command.lights);
  }

  // Handle sensors data
  if (command.sensors != NULL) {
    tank::handleSensors(command.sensors);
  }
}
