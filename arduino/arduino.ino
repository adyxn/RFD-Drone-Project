#include "Arduino.h"
#include <SoftwareSerial.h>

#define motorFL = 1;
#define motorFR = 2;
#define motorBL = 3;
#define motorBR = 4;

const byte rxPin = 9;
const byte txPin = 8;

SoftwareSerial BTSerial(rxPin, txPin);

bool isOn = False;

void turnOn() {
  digitalWrite(motorFL, HIGH);
  digitalWrite(motorFR, HIGH);
  digitalWrite(motorBL, HIGH);
  digitalWrite(motorBR, HIGH);
}

void turnOff() {
  digitalWrite(motorFL, LOW);
  digitalWrite(motorFR, LOW);
  digitalWrite(motorBL, LOW);
  digitalWrite(motorBR, LOW);
}



void setup() {
  pinMode(motorFL, OUTPUT);
  pinMode(motorFR, OUTPUT);
  pinMode(motorBL, OUTPUT);
  pinMode(motorBR, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  BTSerial.begin(9600);
  Serial.begin(9600);

}

String messageBuffer = "";
String message = "";

void loop() {
  while (BTSerial.available() > 0) 
  {
    char data = (char) BTSerial.read();
    messageBuffer += data;
    if (data == ';')
    {
      message = messageBuffer;
      messageBuffer = "";
      Serial.print(message);
      message = "You sent " + message;
      BTSerial.print(message);
      if isOn == true {
        turnOff()
      }
      else if isOn == false {
        turnOn()
      }
    }
  }

}
