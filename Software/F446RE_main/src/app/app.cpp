#include "app.h"

// #include "mode.hpp"
#include "robot.hpp"

Robot robot;
// Mode mode(&robot);

void TimInterrupt1khz() {
      robot.heartBeat();
}

void setup() {
      robot.HardwareInit();
      robot.Motor1A.sound(700, 100);
      robot.Motor2A.sound(800, 100);
      robot.Motor3A.sound(900, 100);
      robot.Motor4A.sound(1000, 100);
      robot.Motor1B.sound(700, 100);
      robot.Motor2B.sound(800, 100);
      robot.Motor3B.sound(900, 100);
      robot.Motor4B.sound(1000, 100);
}

void main_app() {
      while (1) {
            // mode.MainMode();
            robot.Motor1A = 0.2;
            robot.Motor1B = 0;
            HAL_Delay(200);
            robot.Motor1A = 0;
            robot.Motor1B = 0.2;
            HAL_Delay(200);
      }
}