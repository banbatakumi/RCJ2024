#include "app.h"

// #include "mode.hpp"
#include "robot.hpp"

Robot robot;
// Mode mode(&robot);

// void TimInterrupt1khz() {
//       robot.heartBeat();
// }

void setup() {
      robot.hardwareInit();
}

void main_app() {
      while (1) {
            // mode.MainMode();
            robot.led1.write(1);
            robot.motor1a.write(0.5);
            robot.motor1b.write(0);
            HAL_Delay(1000);
            robot.led1.write(0);
            robot.motor1a.write(0);
            robot.motor1b.write(0.5);
            HAL_Delay(1000);
      }
}