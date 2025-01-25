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
#include "kicker.hpp"
#include "main.h"
#include "motor_drive.hpp"

typedef struct {
      float voltage;
      uint8_t motor_rps[4];

      struct {
            uint8_t interval;
            bool is_on_line;
            bool is_leftside;
            bool is_rightside;
            int16_t dir;
            int16_t inside_dir;

            bool on_led;
      } Line;
      struct {
            uint16_t front_val;
            uint16_t front_th;
            bool is_front;
            uint16_t back_val;
            uint16_t back_th;
            bool back_front;
      } Catch;
      struct {
            int16_t yaw;
            int16_t pitch;
            int16_t roll;
      } Imu;

} RobotInfo;
class Robot {
     public:
      Robot();

      // values
      RobotInfo info;

      DigitalOut led1 = DigitalOut(LED1_GPIO_Port, LED1_Pin);
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

      DigitalOut kicker_charge = DigitalOut(KICKER_CHARGE_GPIO_Port, KICKER_CHARGE_Pin);
      DigitalOut kicker_kick = DigitalOut(KICKER_KICK_GPIO_Port, KICKER_KICK_Pin);

      MotorDrive motor = MotorDrive(&motor1a, &motor1b, &motor2a, &motor2b, &motor3a, &motor3b, &motor4a, &motor4b, &info.Imu.yaw, info.motor_rps);
      DribblerDrive dribbler_front = DribblerDrive(&dribbler_front_a, &dribbler_front_b);
      DribblerDrive dribbler_back = DribblerDrive(&dribbler_back_a, &dribbler_back_b);
      Kicker kicker = Kicker(&kicker_charge, &kicker_kick);

      BufferedSerial serial1 = BufferedSerial(&huart1, 128);
      BufferedSerial serial2 = BufferedSerial(&huart2, 256);

      void HardwareInit();
      void GetSensors();

      void RecvImuUart();
      void RecvLineUart();

      inline __attribute__((always_inline)) void heartBeat() {
            static int i = 0;
            i++;
            ledh = abs(MyMath::sinDeg(int(i * (360.0f / 2000.0f))));
      }

     private:
};

#endif