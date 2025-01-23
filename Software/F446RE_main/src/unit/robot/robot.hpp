#ifndef __ROBOT__
#define __ROBOT__

#include "BufferedSerial.hpp"
#include "DigitalInOut.hpp"
#include "MovingAve.hpp"
#include "PWMSingle.hpp"
#include "Timer.hpp"
#include "adc.h"
#include "config.h"
#include "dribbler_drive.hpp"
#include "main.h"
#include "motor_drive.hpp"

class Robot {
     public:
      Robot();

      int yaw, pitch, roll;

      DigitalOut led1 = DigitalOut(GPIOA, LED1_Pin);

      PwmSingleOut ledh = PwmSingleOut(&htim13, TIM_CHANNEL_1);

      PwmSingleOut motor1a = PwmSingleOut(&htim12, TIM_CHANNEL_2);
      PwmSingleOut motor1b = PwmSingleOut(&htim12, TIM_CHANNEL_1);
      PwmSingleOut motor2a = PwmSingleOut(&htim2, TIM_CHANNEL_3);
      PwmSingleOut motor2b = PwmSingleOut(&htim2, TIM_CHANNEL_4);
      PwmSingleOut motor3a = PwmSingleOut(&htim3, TIM_CHANNEL_2);
      PwmSingleOut motor3b = PwmSingleOut(&htim2, TIM_CHANNEL_2);
      PwmSingleOut motor4a = PwmSingleOut(&htim3, TIM_CHANNEL_1);
      PwmSingleOut motor4b = PwmSingleOut(&htim3, TIM_CHANNEL_3);

      PwmSingleOut dribbler_front_a = PwmSingleOut(&htim4, TIM_CHANNEL_1);
      PwmSingleOut dribbler_front_b = PwmSingleOut(&htim4, TIM_CHANNEL_2);
      PwmSingleOut dribbler_back_a = PwmSingleOut(&htim2, TIM_CHANNEL_1);
      PwmSingleOut dribbler_back_b = PwmSingleOut(&htim4, TIM_CHANNEL_4);

      MotorDrive motor = MotorDrive(&motor1a, &motor1b, &motor2a, &motor2b, &motor3a, &motor3b, &motor4a, &motor4b);
      DribblerDrive dribbler_front = DribblerDrive(&dribbler_front_a, &dribbler_front_b);
      DribblerDrive dribbler_back = DribblerDrive(&dribbler_back_a, &dribbler_back_b);

      BufferedSerial serial1 = BufferedSerial(&huart1, 128);

      void HardwareInit();
      void GetSensors();
      void RecvImuUart();

      inline __attribute__((always_inline)) void heartBeat() {
            static int i = 0;
            i++;
            ledh = abs(MyMath::sinDeg(int(i * (360.0f / 2000.0f))));
      }

     private:
};

#endif