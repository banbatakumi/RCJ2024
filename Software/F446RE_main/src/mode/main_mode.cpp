#include "mode.hpp"

// cortex-debug用グローバル変数
int yaw;
float voltage;
int process_freq;
int line_dir;
int is_on_line;
int encoder[4];
int debug[2];

void Mode::MainMode() {
      process_timer.reset();
      robot->ImuUart();
      robot->LineUart();
      robot->GetSensors();
      robot->info.Line.on_led = 1;

      // static float cnt;
      // cnt += 0.05;
      // robot->motor.Drive(cnt, 0.5);
      // robot->dribbler_front.Hold(20);
      // if (robot->info.Catch.is_front) {
      //       robot->kicker.Kick(0.15);
      // }

      // cortex-debug
      yaw = robot->info.Imu.yaw;
      voltage = robot->info.voltage;
      line_dir = robot->info.Line.dir;
      is_on_line = robot->info.Line.is_on_line;

      encoder[0] = robot->info.motor_rps[0];
      encoder[1] = robot->info.motor_rps[1];
      encoder[2] = robot->info.motor_rps[2];
      encoder[3] = robot->info.motor_rps[3];

      debug[0] = robot->info.Catch.front_val;
      debug[1] = robot->info.Catch.back_val;

      //  定周期処理
      process_time_ = process_timer.read_us();
      if (process_time_ < PERIOD_US) {
            while (process_timer.read_us() < PERIOD_US);
      }
      process_freq = 1.0f / (process_timer.read_us() * 0.000001f);
}