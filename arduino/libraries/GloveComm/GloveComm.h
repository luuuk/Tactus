#ifndef GloveComm_h
#define GloveComm_h

#include "Arduino.h"

class GloveComm {
  public:
    GloveComm(String types_[3]);
    void setAxis(String _name, int value);
    void update();
    String types[];
    int vals[];
	int get(String _name);
  private:
    String _buffer;  
    String _keys;
    String _vals;
    String delete(String s, int index);
};

#endif
