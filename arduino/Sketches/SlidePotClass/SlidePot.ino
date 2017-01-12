/*//might need to have the following imports in file using this class as well.
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int margin = 5;//acceptable margin of error for slidepot positioning
const int pwm_speed = 127;//speed for moving slidepot motor. currently constant; may make dynamic later
class SlidePot {
  private:
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor motor;
  
    int pot;//pin for potentiometer (analog pin)
    
    
    int en;//pin for 'enable' on H-bridge (digital pwm pin)
    int fr;//pin for forward motor (digital pin)
    int bk;//pin for backward motor (digital pin)
    
    int force1; //pin for force sensing (current draw)
    int force2; //pin for force sensing (current draw)
    int dest;//destination
    int fMax; //max force before release
    void mov(bool dir, int pwm);//sets motor speed in a given direction; (0 < pwm < 255)
                                //dir true=forward, false=backward
    void stp();// stop motor
    void fre();//let motor freespin
       
  public:
    SlidePot(int _pot, int _en, int _fr, int _bk, int _force, int fMax_);
    void set(int pos);//set destination
    void setForce(int fMax);
    int getPos();//get current pot position
    int getForce1();//amount of force exerted on motor; current draw
    int getForce2();//amount of force exerted on motor; current draw
    void check();//checks current position against destination and moves accordingly
    
};

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

void SlidePot::getPos() {
  return analogRead(pot);
}

void SlidePot::getForce1() {
  return analogRead(force1);//this is just how I imagine this will work; 
                           //there might need to be some mapping/calculations added.
}

void SlidePot::getForce2() {
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
*/



