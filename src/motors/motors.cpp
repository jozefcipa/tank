#include <Arduino.h>

namespace motors {
  const int rightA = A3;
  const int rightB = A2;
  const int leftA = A1;
  const int leftB = A0;

  void setup() {
    pinMode(leftA, OUTPUT);
    pinMode(leftB, OUTPUT);
    pinMode(rightA, OUTPUT);
    pinMode(rightB, OUTPUT);

    Serial.println("Motors configured.");
  }
  
  void move(char motor, char direction) {
    Serial.println("going");
    digitalWrite(leftA, HIGH);
    digitalWrite(leftB, LOW);
    digitalWrite(rightA, HIGH);
    digitalWrite(rightB, LOW);
        Serial.println("wait");

    delay(2000);

        Serial.println("stopping");

    digitalWrite(leftA, LOW);
    digitalWrite(leftB, LOW);
    digitalWrite(rightA, LOW);
    digitalWrite(rightB, LOW);
        Serial.println("wait");

    delay(2000);

    // int motorA;
    // int motorB;
    
    // if (motor == 'L') {
    //   motorA = leftA;
    //   motorB = leftB;
    // } else if (motor == 'R') {
    //   motorA = rightA;
    //   motorB = rightB;
    // } else {
    //   Serial.println("[motors]: Unknown motor: " + motor);
    //   return;
    // }

    // if (direction == 'F') {
    //   // forward
    //   digitalWrite(motorA, LOW);
    //   digitalWrite(motorB, HIGH);
    // } else if (direction == 'B') {
    //   // backward
    //   digitalWrite(motorA, HIGH);
    //   digitalWrite(motorB, LOW);
    // }
    
    // // run for 100ms
    // delay(100);

    // // TODO: how to make it run continuously?

    // // stop motor
    // digitalWrite(motorA, LOW);
    // digitalWrite(motorB, LOW);
  }
}