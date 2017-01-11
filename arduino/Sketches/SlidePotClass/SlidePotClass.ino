#include <GloveComm.h>
#include <Adafruit_MotorShield.h>

GloveComm port;
SlidePot slide;

void setup() {
  // put your setup code here, to run once:
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  slide.set(512);


  port.setAxis("pos", slide.getPos());
  port.setAxis("force", slide.getForce());
  port.sendAll();
}
