#include "Arduino.h"
#include "GloveComm.h"

GloveComm::GloveComm(String types_[3]) {
  Serial.begin(9600);
  _buffer = "";
  types = types_;
}

void GloveComm::setAxis(String _name, int value) {
  _buffer = _buffer + _name + “:” + value + “&”;
}

void GloveComm::update() {
  Serial.println(_buffer);
  _buffer = “&”;
}

String GloveComm::delete(String s, int index) {
  return s.substring(0, index) + "*" + s.substring(index+1);
}

int GloveComm::get(String _name) {
	for(int i = 0; i < types.length; i++){
		if(_name == types[i]) return vals[i];
	}
	return -1; //No value found
}

void GloveComm::serialEvent(){
  String val = readString();
  if (val != null) {
    int firstAnd = val.indexOf("&");
        while (firstAnd > 0 && val.length() > firstAnd + 1) {
          int namePos = firstAnd + 1;
          int firstCol = val.indexOf(":");
          int valPos = firstCol + 1;
          int secondAnd = val.indexOf("&", valPos);
          String name = val.substring(namePos, firstCol);
          int value = int(val.substring(valPos, secondAnd));
          for (int j = 0; j < types.length; j++) 
            if (name == types[j]) vals[j] = value;
          val = delete(val, firstAnd);
          val = delete(val, firstCol);
          firstAnd = val.indexOf("&");
        }
  }
}

/*
find &
next pos = namepos
& = 0;
find :
name = namepos to :
next pos = valuepos
: = 0;
find &
value = valuepos to &

do something with name/value
repeat
*/