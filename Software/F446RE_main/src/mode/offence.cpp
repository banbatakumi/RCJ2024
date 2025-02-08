#include "mode.hpp"

void Mode::Offence() {
      if (robot->info.Line.is_on_line) {
            robot->motor.Drive(robot->info.Line.inside_dir, 0.5);
      } else {
            robot->motor.Drive(robot->info.Cam.ball_dir * 2, 0.5);
      }
}