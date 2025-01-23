#ifndef __MOVING_AVE__
#define __MOVING_AVE__

#include "main.h"

class MovingAve {
     public:
      void Compute(float input);
      void SetLength(uint8_t length_ = 10);
      float Get();
      void Reset();

     private:
      float data_[100];
      float result_;
      uint8_t cnt_;
      uint8_t length_;
};
#endif