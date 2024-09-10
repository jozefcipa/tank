#include <Arduino.h>
#include <SoftwareSerial.h>

namespace bluetooth {
  const int BLUETOOTH_RX = 11;
  const int BLUETOOTH_TX = 10;
  SoftwareSerial btClient(BLUETOOTH_TX, BLUETOOTH_RX);

  void setup() {
    btClient.begin(9600);

    Serial.println("Bluetooth configured.");
  }

  char* read() {
    char data;
    char *response = "";

    while (btClient.available() > 0) {
      data = btClient.read();

      response += data;
      delay(5); // TODO: do we actually need to wait at all?
    }

    return response;
  }

  void send(const char *msg) {
    btClient.write(msg);
  }
}