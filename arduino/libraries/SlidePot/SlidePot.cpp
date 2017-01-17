#include "Arduino.h"
#include "SlidePot.h"
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

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

void SlidePot::mov(bool dir, int pwm) {
  if(dir) {
    motor.run(FORWARD);
  } else {
    motor.run(BACKWARD);
  }
  motor.setSpeed(pwm);
}

void SlidePot::fre() {
  motor.run(RELEASE);
}