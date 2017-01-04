class SlidePot {
  private:
    int pot;//pin for potentiometer
    int en;//pin for 'enable' on H-bridge
    int fr;//pin for forward motor
    int bk;//pin for backward motor
    int dest;//destination
    
  public:
    SlidePot(int _pot, int _en, int _fr, int _bk);
    void set(int pos);//set destination
    int getPos();//get current pot position
    int getForce();//amount of force exerted on motor; current draw
    void check();//checks current position against destination and moves accordingly
};

SlidePot::SlidePot(int _pot, int _en, int _fr, int _ bk) {
  pot = _pot;
  en = _en;
  fr = _fr;
  bk = _bk;
}

void SlidePot::set(int pos) {
  dest = pos;
}

void SlidePot::getPos() {
  return analogRead(pot);
}

void SlidePot::getForce() {
  //TODO
}

void SlidePot::check() {
  //TODO
}



