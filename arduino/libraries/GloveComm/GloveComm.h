#ifndef GloveComm_h
#define GloveComm_h

#include "Arduino.h"

class GloveComm {
  public:
    GloveComm();
    void setAxis(String _name, int value);
    void sendAll();
  private:
    String _buffer;  
};

#endif
