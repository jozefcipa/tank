#include <Arduino.h>
#include <SoftwareSerial.h>

namespace bluetooth {
  const int BLUETOOTH_RX = 13;
  const int BLUETOOTH_TX = 12;
  SoftwareSerial btClient(BLUETOOTH_RX, BLUETOOTH_TX);

  void setup() {
    btClient.begin(9600);

    Serial.println("Bluetooth configured.");
  }

  String read() {
    String message = "";

    while (btClient.available() > 0) {
      message += (char) btClient.read();
      delay(5); // TODO: do we actually need to wait at all?
    }

    message.trim();

    return message;
  }

  void send(const char *msg) {
    btClient.write(msg);
  }
}