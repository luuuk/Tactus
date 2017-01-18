#include "Arduino.h"
#include "SlidePot.h"
/*
The following must be included in the main arduino file:
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
This should cause them to also be added to the path for this file.
*/
const int margin = 5;
const int pwm_speed = 127;

SlidePot::SlidePot(int _pot, int _force1, int _force2) {
  pot = _pot;
  force1 = _force1;
  force2 = _force2;
  AFMS = Adafruit_MotorShield();
  motor = AFMS.getMotor(1);
  AFMS.begin();
}

void SlidePot::set(int pos) {
  dest = pos;
}

int SlidePot::getPos() {
  return analogRead(pot);
}

int SlidePot::getForce1() {
  return analogRead(force1);//this is just how I imagine this will work; 
                           //there might need to be some mapping/calculations added.
}

int SlidePot::getForce2() {
  return analogRead(force2);//this is just how I imagine this will work; 
                           //there might need to be some mapping/calculations added.
}

void SlidePot::check() {
  int potpos = analogRead(pot);
  int diff = dest - potpos;//diff between desired position and actual position
  if(abs(diff) <= margin) return;//if diff is within acceptable margin, return; no adjustment needed.
  mov(diff>0, pwm_speed);
}

void SlidePot::mov(bool dir, int pwm) {//sets the direction and speed of the motor. 
									   //a val of 'true' for dir will make the motor go forward.	
  if(dir) {
    motor->run(FORWARD);//method calls on motor use '->' syntax; it's a pointer
  } else {
    motor->run(BACKWARD);
  }
  motor->setSpeed(pwm);
}

void SlidePot::fre() {//Let the motor spin freely
  motor->run(RELEASE);
}