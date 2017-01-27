/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


int pot = 0;//pin for potentiometer (analog pin)
int force1 = 4; //pin for force sensing (current draw)
int force2 = 5; //pin for force sensing (current draw)
int dest;//destination
int fMax; //max force before release
const int margin = 1;
const int pwm_speed = 100;
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor = AFMS.getMotor(1);
int pos = 512;
boolean vector = true;
int values[3];


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor->setSpeed(150);
  motor->run(FORWARD);
  // turn on motor
  motor->run(RELEASE);
}

void loop() {
  uint8_t i;
  //Serial.println(pos);
  set(analogRead(A1));
  cycle(analogRead(A0));
  //if(vector) pos++;
  //else pos--;
  //if(pos > 1000 || pos < 5) vector = !vector;
  up();
  //delay(10);
  Serial.println(String(values[0]) + ' ' + values[1] + ' ' + values[2]);
  //if (Serial.available() > 0) { pos = Serial.parseFloat(); set(pos); }
  Serial.println("Pos: " + String(dest));
}

void set(int pos) {
  dest = pos;
}

int getPos() {
  return analogRead(pot);
}


void mov(bool dir, int pwm) {//sets the direction and speed of the motor. 
                     //a val of 'true' for dir will make the motor go forward.  
  motor->setSpeed(pwm);
  if(dir) {
    motor->run(FORWARD);//method calls on motor use '->' syntax; it's a pointer
  } else {
    motor->run(BACKWARD);
  } 
}

void cycle(int value) {
  for(int i = 2; i > 0; i--) {
    values[i] = values[i-1];
  }
  values[0] = value;
}

int avg() {
  int tot = 0;
  for(int i = 2; i >= 0; i--) {
    tot += values[i];
  }
  return tot/3;
}

void up() {
  int potpos = avg();
  Serial.println(potpos);
  int diff = dest - potpos;//diff between desired position and actual position
  if(abs(diff) <= margin) return;//if diff is within acceptable margin, return; no adjustment needed.
  mov(diff>0, constrain(pwm_speed+(abs(diff)), 0, 255));
}
