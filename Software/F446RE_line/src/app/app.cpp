#include "app.h"

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
}

void main_app() {
      while (1) {
            process_timer.reset();
            // hardware.RecvImuUart();
            hardware.GetSensors();
            hardware.encoder.Read();

            // cortex-debug

            //  定周期処理
            process_time_ = process_timer.read_us();
            if (process_time_ < PERIOD_US) {
                  while (process_timer.read_us() < PERIOD_US);
            }
            process_freq = 1.0f / (process_timer.read_us() * 0.000001f);
      }
}
