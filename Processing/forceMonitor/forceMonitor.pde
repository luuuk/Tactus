import processing.serial.*;

Serial port; 
int val, num; 
ArrayList<String> names = new ArrayList<String>(); 
HashMap<String, Integer> vals;
int j = 0;

void setup() 
{
  size(800, 400);
  surface.setResizable(true);
  vals = new HashMap<String, Integer>();

  printArray(Serial.list());
  String portName = Serial.list()[1];
  port = new Serial(this, portName, 9600);
  background(255);
  port.bufferUntil('\n');
}

void draw()
{
  //check();
  stroke(0, 255, 0);
  num = vals.size();
  if (num>0) {
    for (int i = 0; i < num; i++) {
      stroke(0);
      rect((i*width/num)+j, 0, 1, height);
      stroke(0, 255, 0);
      //line((i*width/num)+j, map(random(0,1023), 0, 1023, 0, height), (i*width/num)+j, height);
      line((i*width/num)+j, map(vals.get(names.get(i)), 0, 1023, height, 0), (i*width/num)+j, height);
    }
    j = (j+1)%(width/num-3);
  }
}

/*void serialEvent(Serial p) {
 //print("dyfjf");
 //while (port.available() > 0)
 {
 String newline;
 
 //p.readStringUntil('\n');
 //delay(10);
 newline = p.readStringUntil('\n');
 println(newline);
 port.clear();
 //newline = "force 567 lala 875";
 int value = -10;
 if (newline != null) value = int(trim(newline));
 if (value != -10) {
 vals.put("force", value);
 names.add("force");
 }
 }
 }*/