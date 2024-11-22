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
  const int SPEED = 50; // PWM value 1-255

  Motor rightMotor = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
  Motor leftMotor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

  bool motorsRunning = false;

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

    // TODO: this is not good as we control both motors separately, should have two variables, one for each
    motorsRunning = false;
  }
  
  void drive(char motorId, char direction) {
    Motor* motor = getMotor(motorId);
    
    if (motor == NULL) {
      return;
    }

    // First stop the motor 
    stop(motorId);

    switch (direction) {
      case 'F':
        motor->drive(SPEED);
        break;
      case 'B':
        motor->drive(-SPEED);
        break;
      default:
        Serial.println("[motors]: Unknown direction: " + direction);
        return;
    }

    motorsRunning = true;
  }
}