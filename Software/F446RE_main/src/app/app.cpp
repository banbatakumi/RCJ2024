#include "app.h"

// #include "mode.hpp"
#include "robot.hpp"

Robot robot;
//  Mode mode(&robot);

void TimInterrupt1khz() {
      robot.heartBeat();
}

void setup() {
      robot.HardwareInit();
}

void main_app() {
      while (1) {
            // mode.MainMode();
            robot.RecvImuUart();
            robot.motor.Drive(0, 0);
            // robot.dribbler_front.Hold(abs(robot.yaw));
      }
}