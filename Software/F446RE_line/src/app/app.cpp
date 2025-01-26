#include "app.h"

#include "Timer.hpp"
#include "config.h"
#include "hardware.hpp"

Hardware hardware;
Timer process_timer;

uint16_t process_time_;  // us

// cortex-debug
int process_freq;
int encoder[4];

int16_t dir;
uint8_t max_interval;
bool is_half_out;
bool is_on_line;
bool is_leftside_white;
bool is_rightside_white;

void TimInterrupt2khz() {
      hardware.MainUart();
}

void setup() {
      hardware.Init();
      hardware.line.SetTh();
}

void main_app() {
      while (1) {
            process_timer.reset();
            hardware.GetSensors();
            hardware.encoder.Read();
            hardware.line.Read();
            hardware.line.Compute();

            // cortex-debug
            encoder[0] = hardware.info.Encoder.rps[0];
            encoder[1] = hardware.info.Encoder.rps[1];
            encoder[2] = hardware.info.Encoder.rps[2];
            encoder[3] = hardware.info.Encoder.rps[3];

            dir = hardware.info.Line.dir;
            is_half_out = hardware.info.Line.is_half_out;
            is_leftside_white = hardware.info.Line.is_leftside_white;
            is_rightside_white = hardware.info.Line.is_rightside_white;
            is_on_line = hardware.info.Line.is_on_line;
            max_interval = hardware.info.Line.max_interval;

            //  定周期処理
            process_time_ = process_timer.read_us();
            if (process_time_ < PERIOD_US) {
                  hardware.led1 = 1;
                  while (process_timer.read_us() < PERIOD_US);
                  hardware.led1 = 0;
            }
            process_freq = 1.0f / (process_timer.read_us() * 0.000001f);
      }
}
