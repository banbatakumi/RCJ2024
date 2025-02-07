#include "app.h"

#include "MyMath.hpp"
#include "Timer.hpp"
#include "config.h"
#include "hardware.hpp"

Hardware hardware;
Timer process_timer;

uint16_t process_time_;  // us

// cortex-debug
int process_freq;

void setup() {
      hardware.Init();
      hardware.led3 = 1;
      for (float i = 0; i < PI * 4; i += PI * 0.01) {
            hardware.led1 = abs(MyMath::sin(i));
            hardware.led2 = abs(MyMath::sin(i + PI / 4));
            hardware.led3 = abs(MyMath::sin(i + PI / 3));
            hardware.led4 = abs(MyMath::sin(i + PI / 2));
            HAL_Delay(5);
      }
      hardware.led1 = 0;
      hardware.led2 = 0;
      hardware.led3 = 0;
      hardware.led4 = 0;
      for (uint8_t i = 0; i < 5; i++) {
            hardware.led2 = i % 2;
            HAL_Delay(100);
      }
}

void main_app() {
      while (1) {
            process_timer.reset();
            hardware.MainUart();
            hardware.M1nUart();

            hardware.info.ball_dir = 90;
            hardware.info.ball_dis = 40;

            //  定周期処理
            process_time_ = process_timer.read_us();
            if (process_time_ < PERIOD_US) {
                  while (process_timer.read_us() < PERIOD_US);
            }
            process_freq = 1.0f / (process_timer.read_us() * 0.000001f);
      }
}