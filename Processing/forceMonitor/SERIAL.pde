class sComm {
  Serial myPort;
  String val;
  boolean firstContact = false;
  String[] types;
  int[] vals;
  String buff = "";

  sComm(PApplet sketch) {
    myPort = new Serial(sketch, Serial.list()[4], 9600);
    myPort.bufferUntil('\n');
  }

  sComm(PApplet sketch, String[] types_) {
    myPort = new Serial(sketch, Serial.list()[4], 9600);
    myPort.bufferUntil('\n');
    types = types_;
  }
  
  void setAxis(String _name, int _value) {
  buff = buff + " " + _name + " " + _value + " ";
}


  void serialEvent(Serial myPort) {
    val = myPort.readStringUntil('\n');
    if (val != null) {
      val = trim(val);
      println(val);

      if (firstContact == false) {
        if (val.equals("A")) {
          myPort.clear();
          firstContact = true;
          myPort.write("A");
          print("types: ");
          for (int i = 0; i < names.size(); i++) print(types[i] + " ");
          println("end");
        }
      } else { //if we've already established contact, keep getting and parsing data
        println(val);
        String[] tokens = split(val, ' ');
        for(int i = 0; i < tokens.length-1; i += 2)
          for(int j = 0; j < types.length; j++) {
            if(tokens[i] == types[i]) {
              vals[i] = int(tokens[i+1]);
            }
          }

        // when you've parsed the data you have, ask for more:
        myPort.write(buff);
        
        buff = "";
      }
    }
  }
}