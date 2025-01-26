#ifndef __MOTORDRIVE__
#define __MOTORDRIVE__

#include "MovingAve.hpp"
#include "MyMath.hpp"
#include "PWMSingle.hpp"
#include "Timer.hpp"
#include "pid.hpp"

#define MAX_POWER 1000  // MAX:100
#define MIN_POWER 10
#define MOVING_AVE_NUM 5

#define MOTOR_QTY 4

#define CHECK_SPEED 100  // ms

class MotorDrive {
     public:
      MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b,
                 PwmSingleOut *motor2a, PwmSingleOut *motor2b,
                 PwmSingleOut *motor3a, PwmSingleOut *motor3b,
                 PwmSingleOut *motor4a, PwmSingleOut *motor4b,
                 int16_t *yaw, uint8_t *motor_rps);

      void Drive(int16_t deg, uint8_t speed);
      void Run(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
      void Brake();
      void Init();
      void CheckConnection();

     private:
      PwmSingleOut *motor1a_;
      PwmSingleOut *motor1b_;
      PwmSingleOut *motor2a_;
      PwmSingleOut *motor2b_;
      PwmSingleOut *motor3a_;
      PwmSingleOut *motor3b_;
      PwmSingleOut *motor4a_;
      PwmSingleOut *motor4b_;

      MovingAve motor_ave[MOTOR_QTY];

      PID motor_pid[MOTOR_QTY];

      PID pid;
      int16_t *yaw_;
      uint8_t *motor_rps_;

      Timer period_timer;
};

#endif