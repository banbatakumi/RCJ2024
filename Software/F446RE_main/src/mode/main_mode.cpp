#include "mode.hpp"

// cortex-debug用グローバル変数
int yaw;
float voltage;
int process_freq;
int line_dir;

void Mode::MainMode() {
      process_timer.reset();
      robot->RecvImuUart();
      robot->RecvLineUart();
      robot->GetSensors();
      robot->info.Line.on_led = 1;

      if (robot->info.encoder_val[0] > 0) {
            robot->kicker.Kick(0.3);
      } else {
            robot->kicker.Charge();
      }

      // cortex-debug
      yaw = robot->info.Imu.yaw;
      voltage = robot->info.voltage;
      line_dir = robot->info.Line.dir;

      //  定周期処理
      process_time_ = process_timer.read_us();
      if (process_time_ < PERIOD_US) {
            while (process_timer.read_us() < PERIOD_US);
      }
      process_freq = 1.0f / (process_timer.read_us() * 0.000001f);
}