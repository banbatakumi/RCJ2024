#include "robot.hpp"

class Mode {
     public:
      Mode(Robot* robotPtr) : robot(robotPtr) {}
      void MainMode();
      void Offence();
      void Defence();

     private:
      Timer process_timer;
      Robot* robot;

      uint16_t process_time_;  // us
};