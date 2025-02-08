#include "mode.hpp"

void Mode::Offence() {
      if (robot->info.Line.is_on_line) {
            robot->motor.Drive(robot->info.Line.inside_dir, 0.5);
      } else {
            if (robot->info.Catch.is_front) robot->kicker.Kick(0.5);
            robot->motor.Drive(robot->info.Cam.ball_dir * 2, 0.5);
            if (abs(robot->info.Cam.ball_dir) < 20 && robot->info.Cam.ball_dis < 10) {
                  robot->dribbler_front.Hold(50);
            } else {
                  robot->dribbler_front.Hold(0);
            }
      }
}