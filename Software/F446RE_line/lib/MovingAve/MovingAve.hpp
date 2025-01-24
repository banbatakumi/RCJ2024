#ifndef __MOVING_AVE__
#define __MOVING_AVE__

#include "main.h"

class MovingAve {
     public:
      void Compute(double* input_);
      void SetLength(uint8_t length_ = 10);
      void Reset();

      double data[100];
      uint8_t cnt;
      uint8_t length = 10;
};
#endif