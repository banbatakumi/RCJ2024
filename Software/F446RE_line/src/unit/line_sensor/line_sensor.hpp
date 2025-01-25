#ifndef __LINESENSOR__
#define __LINESENSOR__

#include "DigitalInOut.hpp"
#include "MovingAve.hpp"
#include "MyMath.hpp"

#define LINE_QTY 24
#define SET_TH_NUM 5000
#define TH_VALUE 30

class LineSensor {
     public:
      LineSensor(DigitalOut *mux1a, DigitalOut *mux1b,
                 DigitalOut *mux2a, DigitalOut *mux2b,
                 DigitalOut *mux3a, DigitalOut *mux3b,
                 uint8_t *leftside_val, uint8_t *rightside_val,
                 uint8_t *mux1x_val, uint8_t *mux1y_val,
                 uint8_t *mux2x_val, uint8_t *mux2y_val,
                 uint8_t *mux3x_val, uint8_t *mux3y_val);

      void Read();
      void Compute();
      void SetTh();
      bool IsLeft();
      bool IsRight();
      bool IsOnLine();

      bool is_white[LINE_QTY];

      uint8_t white_qty;
      uint8_t max_interval;
      int16_t dir;
      int16_t inside_dir;

     private:
      DigitalOut *mux1a_;
      DigitalOut *mux1b_;
      DigitalOut *mux2a_;
      DigitalOut *mux2b_;
      DigitalOut *mux3a_;
      DigitalOut *mux3b_;

      uint8_t *leftside_;
      uint8_t *rightside_;
      uint8_t *mux1x_;
      uint8_t *mux1y_;
      uint8_t *mux2x_;
      uint8_t *mux2y_;
      uint8_t *mux3x_;
      uint8_t *mux3y_;
};

#endif