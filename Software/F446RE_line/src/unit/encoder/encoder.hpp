#ifndef __ENCODER__
#define __ENCODER__

#include "DigitalInOut.hpp"
#include "MovingAve.hpp"
#include "MyMath.hpp"
#include "Timer.hpp"

class Encoder {
     public:
      Encoder(DigitalOut *led_line, uint8_t *photo_val);

     private:
      uint8_t *photo_val;
};

#endif