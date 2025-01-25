#include "encoder.hpp"

int debug;

Encoder::Encoder(DigitalOut *led_line, uint8_t *photo_val) : led_line_(led_line) {
      this->photo_val_ = photo_val;
      for (uint8_t i = 0; i < SENSOR_QTY; i++) {
            ave[i].SetLength(10);
      }
}

void Encoder::Read() {
      static uint8_t pre_photo_val[SENSOR_QTY];

      // 閾値の自動調整
      for (uint8_t i = 0; i < SENSOR_QTY; i++) {
            if (max_val_[i] < photo_val_[i]) max_val_[i] = photo_val_[i];
            if (min_val_[i] > photo_val_[i]) min_val_[i] = photo_val_[i];
            threshold_[i] = (max_val_[i] + min_val_[i]) * 0.5;
      }

      // 色が変わったらカウント
      for (uint8_t i = 0; i < SENSOR_QTY; i++) {
            is_white_[i] = 0;
            if (photo_val_[i] > threshold_[i]) is_white_[i] = 1;
            if (is_white_[i] != pre_is_white_[i]) {
                  interval_time_us_[i] = interval_timer[i].read_us();
                  interval_timer[i].reset();
            }
            if (interval_timer[i].read_ms() > 100) interval_time_us_[i] = 0;
            ave[i].Compute(interval_time_us_[i]);
            interval_time_s_[i] = ave[i].Get() * 0.000001;
            rps_[i] = 1.0f / (interval_time_s_[i] * 4);

            pre_is_white_[i] = is_white_[i];
      }
      debug = rps_[0];
}