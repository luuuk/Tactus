//#include <GloveComm.h>
//#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//String names[3] = {"val1", "val2", "val3"};

//GloveComm port(names);

String line = "&";
const int margin = 5;//acceptable margin of error for slidepot positioning
const int pwm_speed = 127;//speed for moving slidepot motor. currently constant; may make dynamic later

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(1);

int pot = 0;//pin for potentiometer (analog pin)
/*

  int en;//pin for 'enable' on H-bridge (digital pwm pin)
  int fr;//pin for forward motor (digital pin)
  int bk;//pin for backward motor (digital pin)
*/
int force1 = 4; //pin for force sensing (current draw)
int force2 = 5; //pin for force sensing (current draw)
int dest;//destination
int fMax; //max force before release




void set(int pos) {
  dest = pos;
}

int getPos() {
  return analogRead(pot);
}

int getForce1() {
  return analogRead(force1);//this is just how I imagine this will work;
  //there might need to be some mapping/calculations added.
}

int getForce2() {
  return analogRead(force2);//this is just how I imagine this will work;
  //there might need to be some mapping/calculations added.
}

void check() {
  int potpos = analogRead(pot);
  int diff = dest - potpos;//diff between desired position and actual position
  if (abs(diff) <= margin) return; //if diff is within acceptable margin, return; no adjustment needed.
  mov(diff > 0, pwm_speed);
}

void mov(bool dir, int pwm) {
  if (dir) {
    motor->run(FORWARD);
  } else {
    motor->run(BACKWARD);
  }
  motor->setSpeed(pwm);
}

void fre() {
  motor->run(RELEASE);
}





void setup() {
  // put your setup code here, to run once:
  //port = new GloveComm(names);
  Serial.begin(9600);
  AFMS.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  set(512);
  check();

  //port.setAxis("pot", slide.getPos());
  //port.setAxis("force1", slide.getForce1());
  //port.setAxis("force2", slide.getForce2());

  //port.sendAll();
  String l1 = "&pot:";
  String l2 = "&force1:";
  String l3 = "&force2:";
  
  line = l1 + getPos() +l2 + getForce1() + l3 + getForce2() + String("&");
  Serial.println(line);
}

