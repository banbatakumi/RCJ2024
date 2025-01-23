#include "pid.hpp"

PID::PID() {
}

void PID::SetGain(float kp, float ki, float kd) {
      this->kp_ = kp;
      this->ki_ = ki;
      this->kd_ = kd;
}

void PID::SetSamplingFreq(uint16_t sampling_freq) {
      this->sampling_period_ = 1.0f / sampling_freq;
}

void PID::SetLimit(uint16_t limit) {
      this->limit_ = limit;
}

void PID::Compute(float input_, float target_) {
      if (sampling_timer.read() > sampling_period_) {            // 普通のやつ
            p_ = target_ - input_;                               // 比例
            d_ = (p_ - pre_p_) / sampling_timer.read();          // 微分
            i_ += (p_ + pre_p_) * sampling_timer.read() * 0.5f;  // 台形積分
            if (abs(i_) > limit_) i_ = limit_ * (i_ / abs(i_));
            pre_p_ = p_;

            pid_ = p_ * kp_ + i_ * ki_ + d_ * kd_;

            if (abs(pid_) > limit_) {
                  pid_ = limit_ * (abs(pid_) / pid_);
            }

            sampling_timer.reset();
      }
}

float PID::Get() {
      return pid_;
}