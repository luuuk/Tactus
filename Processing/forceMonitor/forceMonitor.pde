import processing.serial.*;

int val = 0;
int num = 3; //must = the length of the array passed to the port object
int j = 0;
sComm port;
int[][] vals;
int smoothing = 1;
String[] names = {"pot", "force1", "force2"};


void setup() 
{
  size(800, 400);
  port = new sComm(this, names);
  printArray(Serial.list());
  background(255);
  vals = new int[num][width];
}

void draw()
{
  //check();
  stroke(0, 255, 0);
  if (num>0) {
    for (int i = 0; i < num; i++) {
      vals[i][j] = port.vals[i]; //save most recent new value as current name/time value
      stroke(0);
      rect((i*width/num)+j, 0, 1, height);
      stroke(0, 255, 0);
      line((i*width/num)+j, map(avg(i, j), 0, 1023, height, 0), (i*width/num)+j, height);
    }
      
    j = (j+1)%(width/num-3);
  }
}

int avg(int q, int w) {
  int total = 0;
  for(int i = w; i <= w+smoothing; i++) total += vals[q][i];
  total /= (smoothing)+1;
  return vals[q][w];
}