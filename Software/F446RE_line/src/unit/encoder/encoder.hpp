#ifndef __ENCODER__
#define __ENCODER__

#include "DigitalInOut.hpp"
#include "MovingAve.hpp"
#include "MyMath.hpp"
#include "Timer.hpp"

#define SENSOR_QTY 4

class Encoder {
     public:
      Encoder(DigitalOut *led_line, uint8_t *photo_val);

      void Read();
      uint8_t GetSpeed(uint8_t sensor_num);
      void GetVal();

     private:
      uint8_t *photo_val_;
      DigitalOut *led_line_;

      uint16_t speed_[SENSOR_QTY];
      uint16_t rps_[SENSOR_QTY];
      float interval_time_s_[SENSOR_QTY];
      uint16_t interval_time_us_[SENSOR_QTY];
      uint8_t threshold_[SENSOR_QTY];
      uint8_t min_val_[SENSOR_QTY] = {255, 255, 255, 255};
      uint8_t max_val_[SENSOR_QTY];
      uint8_t count_[SENSOR_QTY];
      bool is_white_[SENSOR_QTY];
      bool pre_is_white_[SENSOR_QTY];

      Timer interval_timer[SENSOR_QTY];
      MovingAve ave[SENSOR_QTY];
};

#endif