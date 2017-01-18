#ifndef SlidePot_h
#define SlidePot_h

#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

class SlidePot {
  private:
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor * motor;
    
    int pot;//pin for potentiometer (analog pin)
    
    /*
    int en;//pin for 'enable' on H-bridge (digital pwm pin)
    int fr;//pin for forward motor (digital pin)
    int bk;//pin for backward motor (digital pin)
    */
    
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

#endif