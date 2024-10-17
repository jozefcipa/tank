#include <Arduino.h>
#include <string.h>
#include "tank.h"

namespace tank {
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
}