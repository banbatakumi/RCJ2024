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

      DigitalOut Led1 = DigitalOut(GPIOA, LED1_Pin);

      PwmSingleOut LedH = PwmSingleOut(&htim13, TIM_CHANNEL_1);

      PwmSingleOut Motor1A = PwmSingleOut(&htim12, TIM_CHANNEL_1);
      PwmSingleOut Motor1B = PwmSingleOut(&htim12, TIM_CHANNEL_2);
      PwmSingleOut Motor2A = PwmSingleOut(&htim2, TIM_CHANNEL_4);
      PwmSingleOut Motor2B = PwmSingleOut(&htim2, TIM_CHANNEL_3);
      PwmSingleOut Motor3A = PwmSingleOut(&htim3, TIM_CHANNEL_2);
      PwmSingleOut Motor3B = PwmSingleOut(&htim2, TIM_CHANNEL_2);
      PwmSingleOut Motor4A = PwmSingleOut(&htim3, TIM_CHANNEL_1);
      PwmSingleOut Motor4B = PwmSingleOut(&htim3, TIM_CHANNEL_3);

      PwmSingleOut DribblerFrontA = PwmSingleOut(&htim4, TIM_CHANNEL_1);
      PwmSingleOut DribblerFrontB = PwmSingleOut(&htim4, TIM_CHANNEL_2);
      PwmSingleOut DribblerBackA = PwmSingleOut(&htim2, TIM_CHANNEL_1);
      PwmSingleOut DribblerBackB = PwmSingleOut(&htim4, TIM_CHANNEL_4);

      // BufferedSerial serial6 = BufferedSerial(&huart6, 128);

      void HardwareInit();
      void GetSensors();

      inline __attribute__((always_inline)) void heartBeat() {
            static int i = 0;
            i++;
            LedH.write(abs(MyMath::sinDeg(int(i * (360.0f / 2000.0f)))));
      }

     private:
};

#endif