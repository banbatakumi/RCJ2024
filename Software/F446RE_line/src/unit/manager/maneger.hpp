#ifndef __MANEGER__
#define __MANEGER__

#include "BufferedSerial.hpp"
#include "DigitalInOut.hpp"
#include "MyMath.hpp"
#include "adc.h"
#include "encoder.hpp"
#include "line_sensor.hpp"

typedef struct {
      struct {
            uint8_t leftside, rightside;
            uint8_t mux1x, mux1y;
            uint8_t mux2x, mux2y;
            uint8_t mux3x, mux3y;
      } Line;
} Info;

class Maneger {
     public:
      Maneger();

      // values
      Info info;

      DigitalOut led1 = DigitalOut(LED1_GPIO_Port, LED1_Pin);
      DigitalOut led2 = DigitalOut(LED2_GPIO_Port, LED2_Pin);
      DigitalOut led3 = DigitalOut(LED3_GPIO_Port, LED3_Pin);

      DigitalOut mux1a = DigitalOut(MUX1A_GPIO_Port, MUX1A_Pin);
      DigitalOut mux1b = DigitalOut(MUX1B_GPIO_Port, MUX1B_Pin);
      DigitalOut mux2a = DigitalOut(MUX2A_GPIO_Port, MUX2A_Pin);
      DigitalOut mux2b = DigitalOut(MUX2B_GPIO_Port, MUX2B_Pin);
      DigitalOut mux3a = DigitalOut(MUX3A_GPIO_Port, MUX3A_Pin);
      DigitalOut mux3b = DigitalOut(MUX3B_GPIO_Port, MUX3B_Pin);

      BufferedSerial serial6 = BufferedSerial(&huart6, 256);

      LineSensor line_sensor = LineSensor(&mux1a, &mux1b, &mux2a, &mux2b, &mux3a, &mux3b,
                                          &info.Line.leftside, &info.Line.rightside,
                                          &info.Line.mux1x, &info.Line.mux1y,
                                          &info.Line.mux2x, &info.Line.mux2y,
                                          &info.Line.mux3x, &info.Line.mux3y);

      void
      HardwareInit();
      void GetSensors();

      void RecvImuUart();

     private:
};

#endif