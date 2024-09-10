// Docs
// https://electronoobs.com/eng_arduino_tut77.php
// https://arduino.stackexchange.com/a/57297/92010

#include <Arduino.h>
#include <Wire.h>

namespace compass {
  const int ADDRESS = 0x1E; // 0011110b, I2C 7bit address of HMC5883

  void setup(){
    //Put the HMC5883 IC into the correct operating mode
    Wire.beginTransmission(ADDRESS); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();

    Serial.println("Compass configured.");
  }

  int read(){
    int x, y, z;

    //Tell the HMC5883 where to begin reading data
    Wire.beginTransmission(ADDRESS);
    Wire.write(0x03); //select register 3, X MSB register
    Wire.endTransmission();
  
    //Read data from each axis, 2 registers per axis
    Wire.requestFrom(ADDRESS, 6);
    if (6<=Wire.available()) {
      x = Wire.read() << 8; //X msb
      x |= Wire.read(); //X lsb
      z = Wire.read() << 8; //Z msb
      z |= Wire.read(); //Z lsb
      y = Wire.read() << 8; //Y msb
      y |= Wire.read(); //Y lsb
    }

    // TODO: figure out what exactly is being returned and how to use that value
    return (int) (atan2(y, x) * 180 / M_PI);
  }
}