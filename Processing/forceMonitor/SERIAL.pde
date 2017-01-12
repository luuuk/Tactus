class sComm {
  Serial myPort;
  String val;
  boolean firstContact = false;
  String[] types;
  int[] vals = new int[3];
  String buff = "";

  sComm(PApplet sketch) {
    myPort = new Serial(sketch, Serial.list()[3], 9600);
    myPort.bufferUntil('\n');
  }

  sComm(PApplet sketch, String[] types_) {
    myPort = new Serial(sketch, Serial.list()[3], 9600);
    myPort.bufferUntil('\n');
    types = types_;
  }

  void setAxis(String _name, int _value) {
    buff = buff + _name + ":" + _value + "&";
  }

  String delete(String s, int index) {
    return s.substring(0, index) + "*" + s.substring(index+1);
  }

  void serialEvent(Serial myPort) {
    val = myPort.readStringUntil('\n');
    if (val != null) {
      val = trim(val);
      println(val);

      int firstAnd = val.indexOf("&");
      while (firstAnd > 0 && val.indexOf("&", firstAnd) > 0) {
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


      // when you've parsed the data you have, ask for more:
      myPort.write(buff);

      buff = "&";
    }
  }
}