#ifndef __PID__
#define __PID__

#include "MyMath.hpp"
#include "Timer.hpp"

class PID {
     public:
      PID();

#define PID_TYPE 0
#define PI_D_TYPE 1

      void SetGain(float kp, float ki, float kd);
      void SetSamplingFreq(uint16_t sampling_freq = 100);
      void SetLimit(uint16_t limit = 100);

      void Compute(float input, float target);
      float Get();

     private:
      float p_, i_, d_;
      float pre_p_;
      float kp_, ki_, kd_;
      float pid_;

      float sampling_period_;
      uint16_t limit_;

      Timer sampling_timer;
};

#endif