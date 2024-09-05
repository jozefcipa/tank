#include <Arduino.h>

// const int leftA=A0;
// const int leftB=A1;

const int rightA=A2;
const int rightB=A3;

const int LED = 13;

void setupMotors() {
  // put your setup code here, to run once:
  // pinMode(leftA, OUTPUT);
  // pinMode(leftB, OUTPUT);
  pinMode(rightA, OUTPUT);
  pinMode(rightB, OUTPUT);

  pinMode(LED, OUTPUT);
}
 
void TODO_motors() {
  
  // blink
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);

  // turn
  // digitalWrite(leftA,LOW);
  // digitalWrite(leftB,HIGH);
  digitalWrite(rightA,LOW);
  digitalWrite(rightB,HIGH);

  // wait
  delay(500);
  
  // blink
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);

  // turn
  // digitalWrite(leftA,HIGH);
  // digitalWrite(leftB,LOW);
  digitalWrite(rightA,HIGH);
  digitalWrite(rightB,LOW);

  // wait
  delay(500);
}

