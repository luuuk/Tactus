#include "Arduino.h"
#include "GloveComm.h"

GloveComm::GloveComm() {
  Serial.begin(9600);
  _buffer = "";
}

void GloveComm::setAxis(String _name, int value) {
  _buffer = _buffer + " " + _name + " " + value + " ";
}

void GloveComm::sendAll() {
  Serial.println(_buffer);
  _buffer = "";
}

