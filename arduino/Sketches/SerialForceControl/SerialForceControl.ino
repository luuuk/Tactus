const int MTRS = 1;
int forces[MTRS];
int positions[MTRS];
String buff = "";
void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  getForce();
  
  //actuate motors and scan motor positions into position array

  sendPos();
}

//sends the positions array as formatted name:value pairs
void sendPos() {
  //set up buff
  for (int i = 0; i < MTRS; i++)
    buff += "&" + String(i) + ":" + String(positions[i]);

  //send and reset buff
  Serial.println(buff);
  buff = "";
}

//saves name:value pairs into the forces array
void getForce() {
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
        if (mtrNum < MTRS && mtrNum > 0)
          forces[mtrNum] = force;
      }
      // Find the next command in input string
      command = strtok(0, "&");
    }
  }
}

