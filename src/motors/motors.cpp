#include <Arduino.h>
// https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide/all
#include <SparkFun_TB6612.h>

namespace motors {
  // Right motor
  const int AIN1 = 2;
  const int AIN2 = 3;
  const int PWMA = 4;
  // Left motor
  const int BIN1 = 5;
  const int BIN2 = 6;
  const int PWMB = 7;
  const int STBY = 8;
  const int offsetA = 1;
  // this motor has swapped wires (and I was lazy to fix them),
  // so we can use -1 to reverse direction
  const int offsetB = -1;
  const int SPEED = 150; // PWM value 1-255

  Motor rightMotor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
  Motor leftMotor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

  Motor* getMotor(char motorId) {
    switch (motorId) {
      case 'R': return &rightMotor;
      case 'L': return &leftMotor;
      default:
        Serial.println("[motors]: Unknown motor: " + motorId);
        return NULL;
    }
  }

  void stop(char motorId) {
    Motor* motor = getMotor(motorId);
    
    if (motor == NULL) {
      return;
    }

    motor->brake();
  }

  void driveInDirection(char motorId, char direction, int speed) {
    Motor* motor = getMotor(motorId);
    
    if (motor == NULL) {
      return;
    }

    switch (direction) {
      case 'F':
        motor->drive(speed);
        break;
      case 'B':
        motor->drive(-speed);
        break;
      case '0':
        // do nothing, motor should be stopped
        break;
      default:
        Serial.println("[motors]: Unknown direction: " + direction);
        return;
    }
  }
  
  void drive(char motorA, char directionA, char motorB, char directionB) {
    // First stop the motors
    // stop(motorA);
    // stop(motorB);

    // we start the motors gradually using PWM
    for (int currentSpeed = 0; currentSpeed < SPEED; currentSpeed += 10) {
      driveInDirection(motorA, directionA, currentSpeed);
      driveInDirection(motorB, directionB, currentSpeed);
      delay(10);
    }
  }
}