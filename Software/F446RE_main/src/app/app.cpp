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
            robot.motor.Drive(0, 30);
            HAL_Delay(500);
            robot.motor.Drive(90, 30);
            HAL_Delay(500);
            robot.motor.Drive(180, 30);
            HAL_Delay(500);
            robot.motor.Drive(270, 30);
            HAL_Delay(500);
      }
}