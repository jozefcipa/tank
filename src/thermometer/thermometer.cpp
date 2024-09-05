// Docs
// https://github.com/Sensirion/arduino-i2c-sht4x

#include <SensirionI2cSht4x.h>
#include <Wire.h>
#include "thermometer.h"

static SensirionI2cSht4x _THERMOMETER_sensor;

static char errorMessage[64];
static int16_t error;

void THERMOMETER_setup() {
  _THERMOMETER_sensor.begin(Wire, SHT40_I2C_ADDR_44);
  _THERMOMETER_sensor.softReset();
  delay(10);

  uint32_t serialNumber = 0;
  error = _THERMOMETER_sensor.serialNumber(serialNumber);
  if (error != 0) {
      Serial.print("Error trying to execute serialNumber(): ");
      errorToString(error, errorMessage, sizeof errorMessage);
      Serial.println(errorMessage);
      return;
  }

  Serial.print("Thermometer configured (Serial Number: ");
  Serial.print(serialNumber);
  Serial.println(")");
}

struct TemperatureHumidity THERMOMETER_read() {
    struct TemperatureHumidity data;
    data.temperature = 0.0;
    data.humidity = 0.0;

    error = _THERMOMETER_sensor.measureLowestPrecision(data.temperature, data.humidity);
    if (error != 0) {
        Serial.print("[Thermometer]: Error trying to execute measureLowestPrecision(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
    }

    return data;
}
