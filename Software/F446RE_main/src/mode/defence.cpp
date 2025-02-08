#include "mode.hpp"

void Mode::Defence() {
      if (robot->info.Cam.ball_dir > 0) {
            robot->motor.Drive(90, abs(robot->info.Cam.ball_dir) / 30.000);
      } else {
            robot->motor.Drive(-90, abs(robot->info.Cam.ball_dir) / 30.000);
      }
}