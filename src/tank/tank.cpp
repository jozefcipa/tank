#include <Arduino.h>
#include <string.h>
#include "tank.h"

struct TankCommand TANK_parseMessage(char *msgStr) {
  TankCommand command = {};

  // Split by ';' to get commands for individual peripheries
  char *peripheryCmd = strtok(msgStr, ";");

  while (peripheryCmd != NULL) {
    // Split by '=' to separate key and value
    char *key = strtok(peripheryCmd, "=");
    char *value = strtok(NULL, "=");

    // Compare the key and assign the value to the correct field
    if (strcmp(key, "lights") == 0) {
      strcpy(command.lights, value);
    } else if (strcmp(key, "sensors") == 0) {
      strcpy(command.sensors, value);
    } else if (false) {
      // TODO: implement others
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
