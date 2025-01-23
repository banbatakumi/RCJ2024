#ifndef __DRIBBLERDRIVE__
#define __DRIBBLERDRIVE__

#include "MovingAve.hpp"
#include "PWMSingle.hpp"

#define MAX_POWER 100  // MAX:100
#define MIN_POWER 5
#define MOVING_AVE_NUM 10

#define CHECK_SPEED 100  // ms

class DribblerDrive {
     public:
      DribblerDrive(PwmSingleOut *motor_a, PwmSingleOut *motor_b);

      void Hold(uint8_t power);
      void Kick();
      void Brake();
      void Init();
      void CheckConnection();

     private:
      PwmSingleOut *motor_a_;
      PwmSingleOut *motor_b_;

      MovingAve ave;
};

#endif