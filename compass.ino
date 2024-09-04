// Docs
// https://electronoobs.com/eng_arduino_tut77.php
// https://arduino.stackexchange.com/a/57297/92010

#include <Wire.h>

static int _COMPASS_address = 0x1E; //0011110b, I2C 7bit address of HMC5883

void COMPASS_setup(){
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(_COMPASS_address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

  Serial.println("Compass configured.");
}

float COMPASS_read(){
  int x, y, z;

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(_COMPASS_address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
 
  //Read data from each axis, 2 registers per axis
  Wire.requestFrom(_COMPASS_address, 6);
  if (6<=Wire.available()) {
    x = Wire.read() << 8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read() << 8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read() << 8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  // TODO: figure out what exactly is being returned and how to use that value
  return atan2(y, x) * 180 / M_PI;
}