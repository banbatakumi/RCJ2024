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

#define VOLTAGE_CONVERTION 0.01298828125

typedef struct {
      float voltage;
      uint8_t motor_rps[4];

      uint8_t mode;

      float moving_speed, line_moving_speed;
      struct {
            bool is_initialized = 0;

            uint8_t interval;
            uint8_t depth;
            bool is_on_line;
            bool is_leftside;
            bool is_rightside;
            int16_t dir;
            int16_t inside_dir;

            bool on_led;
      } Line;
      struct {
            uint16_t front_val;
            bool is_front;
            uint16_t back_val;
            bool is_back;
      } Catch;
      struct {
            bool is_initialized = 0;

            int16_t yaw;
            int16_t pitch;
            int16_t roll;
      } Imu;

      struct {
            bool set_yaw_zero;
            uint8_t dribbler_sig;
      } Ui;

      struct {
            bool is_initialized = 0;

            int16_t ball_dir;
            int16_t ball_dis;
            int16_t yellow_goal_dir;
            int16_t yellow_goal_height;
            int16_t blue_goal_dir;
            int16_t blue_goal_height;
            int8_t own_x;
            int8_t own_y;
            int16_t center_dir;
            int16_t center_dis;

            bool is_goal_front;
            uint8_t proximity[4];
      } Cam;

      struct {
            bool is_initialized = 0;
            bool is_connected = 0;
            bool is_moving = 0;
            bool is_catching_ball = 0;
      } Bluetooth;

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

      BufferedSerial serial1 = BufferedSerial(&huart1, 128);  // imu
      BufferedSerial serial2 = BufferedSerial(&huart2, 256);  // line
      BufferedSerial serial3 = BufferedSerial(&huart3, 256);  // ui
      BufferedSerial serial4 = BufferedSerial(&huart4, 256);  // ui

      void HardwareInit();
      void GetSensors();

      void ImuUart();
      void LineUart();
      void UiUart();
      void CamUart();

      Timer line_send_interval_timer;
      Timer ui_send_interval_timer;
      Timer cam_send_interval_timer;

      MovingAve catch_front;
      MovingAve catch_back;

      inline __attribute__((always_inline)) void heartBeat() {
            static int i = 0;
            i++;
            ledh = abs(MyMath::sinDeg(int(i * (360.0f / 2000.0f))));
      }

     private:
};

#endif