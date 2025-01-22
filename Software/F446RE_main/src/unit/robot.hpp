#ifndef __ROBOT__
#define __ROBOT__

#include "DigitalInOut.hpp"
#include "MovingAve.hpp"
#include "PWMSingle.hpp"
#include "Timer.hpp"
#include "adc.h"
#include "config.h"
#include "main.h"

class Robot {
     public:
      Robot();

      int yaw;

      DigitalOut led1 = DigitalOut(GPIOA, LED1_Pin);
      DigitalOut led2 = DigitalOut(GPIOB, LED2_Pin);

      PwmSingleOut motor1a = PwmSingleOut(&htim12, TIM_CHANNEL_1);
      PwmSingleOut motor1b = PwmSingleOut(&htim12, TIM_CHANNEL_2);

      // BufferedSerial serial6 = BufferedSerial(&huart6, 128);

      void hardwareInit();
      void getSensors();
      void LineCompute();

      // inline __attribute__((always_inline)) void heartBeat() {
      //       static int i = 0;
      //       i++;
      //       led2.write(abs(MyMath::sinDeg(int(i * (360.0f / 2000.0f)))));
      // }

     private:
};

#endif