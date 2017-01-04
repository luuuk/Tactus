class sComm {
  Serial myPort;
  String val;
  boolean firstContact = false;
  //HashMap<String, Integer> vals; 
  String[] types;
  int[] vals;

  sComm(PApplet sketch) {
    myPort = new Serial(sketch, Serial.list()[4], 9600);
    myPort.bufferUntil('\n');
  }

  sComm(PApplet sketch, String[] types_) {
    myPort = new Serial(sketch, Serial.list()[4], 9600);
    myPort.bufferUntil('\n');
    types = types_;
  }

  void serialEvent( Serial myPort) {
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

        for

        // when you've parsed the data you have, ask for more:
        myPort.write("A");
      }
    }
  }
}