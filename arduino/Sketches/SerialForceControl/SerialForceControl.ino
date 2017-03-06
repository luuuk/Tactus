#include <Servo.h>
Servo servo;
const int MTRS = 1;
int forces[MTRS + 2];
int positions[MTRS];
String buff = "";
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(9);
}

void loop() {
  //getForce();

  servo.write(map(forces[0], 0, 180, 0, 160));
  //delay(15);
  positions[0] = analogRead(A0);

  //actuate motors and scan motor positions into position array

  sendPos();
}

//sends the positions array as formatted name:value pairs
void sendPos() {
  //set up buff
  //positions[0] = forces[0];
  for (int i = 0; i < MTRS; i++)
    buff += "&" + String(i) + ":" + String(positions[i]) + "&" + (String(i + 1)) + ":" + String(700 - positions[i]);
  //buff = String(positions[0]);
  //send and reset buff
  Serial.println(buff);
  buff = "";
}

//saves name:value pairs into the forces array
void serialEvent() {
  //bring in serial values
  if (Serial.available() > 0) {
    // Get next command from Serial (add 1 for final 0)
    char input[31];
    byte s = Serial.readBytes(input, 30);
    // Add the final 0 to end the C string
    input[s] = 0;
    // Read each command pair
    char* command = strtok(input, "&");
    while (command != 0) {
      // Split the command in two values
      char* separator = strchr(command, ':');
      if (separator != 0) {
        // Actually split the string in 2: replace ':' with 0
        *separator = 0;
        int mtrNum = atoi(command);
        ++separator;
        int force = atoi(separator);
        if (mtrNum < MTRS && mtrNum >= 0 && force != 0)// && abs(forces[mtrNum]-force) < 20)
          forces[mtrNum] = force;
      }
      // Find the next command in input string
      command = strtok(0, "&");
    }
  }
}

/*void getForces() {
  if (Serial.available() > 0) {
    String newline = Serial.readStringUntil('\n');
    String[] pairs = newline.split('&');
    for (int i = 0; i < pairs.length; i += 1)
    {
      int colon = pairs [i].IndexOf (":");
      int n = int.Parse (pairs [i].Substring (0, colon));
      int val = int.Parse (pairs [i].Substring (colon + 1));
      forces[n] = val;
    }
  }
}*/

