const int margin = 5;//acceptable margin of error for slidepot positioning
class SlidePot {
  private:
    int pot;//pin for potentiometer
    int en;//pin for 'enable' on H-bridge
    int fr;//pin for forward motor
    int bk;//pin for backward motor
    int force; //pin for force sensing (current draw)
    int dest;//destination
    
  public:
    SlidePot(int _pot, int _en, int _fr, int _bk, int _force);
    void set(int pos);//set destination
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
  int diff = potpos-dest;//diff between desired position and actual position
  if(abs(diff) <= margin) return;//if diff is within acceptable margin, return; no adjustment needed.
  
}



