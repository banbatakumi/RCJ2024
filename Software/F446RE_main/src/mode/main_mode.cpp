#include "mode.hpp"

// cortex-debug用グローバル変数
int yaw;
float voltage;
int process_freq;
int line_dir;
int is_on_line;
int encoder[4];

void Mode::MainMode() {
      process_timer.reset();
      robot->RecvImuUart();
      robot->RecvLineUart();
      robot->GetSensors();
      robot->info.Line.on_led = 1;  // 使えない

      // cortex-debug
      yaw = robot->info.Imu.yaw;
      voltage = robot->info.voltage;
      line_dir = robot->info.Line.dir;
      is_on_line = robot->info.Line.is_on_line;

      encoder[0] = robot->info.motor_rps[0];
      encoder[1] = robot->info.motor_rps[1];
      encoder[2] = robot->info.motor_rps[2];
      encoder[3] = robot->info.motor_rps[3];

      //  定周期処理
      process_time_ = process_timer.read_us();
      if (process_time_ < PERIOD_US) {
            while (process_timer.read_us() < PERIOD_US);
      }
      process_freq = 1.0f / (process_timer.read_us() * 0.000001f);
}