const int margin = 5;//acceptable margin of error for slidepot positioning
const int pwm_speed = 127;//speed for moving slidepot motor. currently constant; may make dynamic later
class SlidePot {
  private:
    int pot;//pin for potentiometer (analog pin)
    int en;//pin for 'enable' on H-bridge (digital pwm pin)
    int fr;//pin for forward motor (digital pin)
    int bk;//pin for backward motor (digital pin)
    int force; //pin for force sensing (current draw)
    int dest;//destination
    int fMax; //max force before release
    void mov(bool dir, int pwm);//sets motor speed in a given direction; (0 < pwm < 255)
                                //dir true=forward, false=backward
    
  public:
    SlidePot(int _pot, int _en, int _fr, int _bk, int _force, int fMax_);
    void set(int pos);//set destination
    void setForce(int fMax);
    int getPos();//get current pot position
    int getForce();//amount of force exerted on motor; current draw
    void check();//checks current position against destination and moves accordingly
    
};

SlidePot::SlidePot(int _pot, int _en, int _fr, int _ bk, int _force) {
  pot = _pot;
  en = _en;
  fr = _fr;
  bk = _bk;
  force = _force;
  fMax = fMax_;
}

void SlidePot::set(int pos) {
  dest = pos;
}

void SlidePot::getPos() {
  return analogRead(pot);
}

void SlidePot::getForce() {
  return analogRead(force);//this is just how I imagine this will work; 
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
    digitalWrite(fr, HIGH);
    digitalWrite(bk, LOW);
  } else {
    digitalWrite(bk, HIGH);
    digitalWrite(fr, LOW);
  }
  analogWrite(en, pwm);
}




