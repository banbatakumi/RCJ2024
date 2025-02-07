#include "mode.hpp"

void Mode::Defence() {
      if (robot->info.Cam.ball_dir > 45) {
            robot->motor.Drive(90, abs(45 - robot->info.Cam.ball_dir) / 45.000);
      } else {
            robot->motor.Drive(-90, abs(45 - robot->info.Cam.ball_dir) / 45.000);
      }
}