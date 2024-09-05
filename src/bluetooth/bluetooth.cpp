#include <Arduino.h>
#include <SoftwareSerial.h>

#define _BLUETOOTH_RX 11
#define _BLUETOOTH_TX 10

SoftwareSerial _BLUETOOTH_client(_BLUETOOTH_TX, _BLUETOOTH_RX);

void BLUETOOTH_setup() {
  _BLUETOOTH_client.begin(9600);

  Serial.println("Bluetooth configured.");
}

String BLUETOOTH_read() {
  char data;
  String response = "";

  while (_BLUETOOTH_client.available() > 0) {
    data = _BLUETOOTH_client.read();

    response += data;
    delay(5); // TODO: do we actually need to wait at all?
  }

  response.trim();
  return response;
}

void BLUETOOTH_send(const char *msg) {
  _BLUETOOTH_client.write(msg);
}
