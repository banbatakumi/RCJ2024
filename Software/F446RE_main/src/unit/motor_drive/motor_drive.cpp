#include "motor_drive.hpp"

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b,
                       PwmSingleOut *motor2a, PwmSingleOut *motor2b,
                       PwmSingleOut *motor3a, PwmSingleOut *motor3b,
                       PwmSingleOut *motor4a, PwmSingleOut *motor4b, int16_t *yaw)
    : motor1a_(motor1a), motor1b_(motor1b), motor2a_(motor2a), motor2b_(motor2b), motor3a_(motor3a), motor3b_(motor3b), motor4a_(motor4a), motor4b_(motor4b) {
      this->yaw_ = yaw;
      motor1_ave.SetLength(MOVING_AVE_NUM);
      motor2_ave.SetLength(MOVING_AVE_NUM);
      motor3_ave.SetLength(MOVING_AVE_NUM);
      motor4_ave.SetLength(MOVING_AVE_NUM);

      pid.SetGain(2, 0.5, 0.1);
      pid.SetLimit(100);
      pid.SetSamplingFreq(100);
}

void MotorDrive::Init() {
      motor1a_->init();
      motor1b_->init();
      motor2a_->init();
      motor2b_->init();
      motor3a_->init();
      motor3b_->init();
      motor4a_->init();
      motor4b_->init();
}

void MotorDrive::Drive(int16_t deg, uint8_t speed) {
      int8_t power[MOTOR_QTY];

      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            power[i] = MyMath::sinDeg(deg - (45 + (90 * i))) * speed;
      }

      uint8_t max_power = 0;
      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            if (max_power < abs(power[i])) max_power = abs(power[i]);
      }
      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            power[i] *= float(speed) / max_power;
      }

      pid.Compute(0, *yaw_);
      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            power[i] -= pid.Get();
      }

      Run(power[0], power[1], power[2], power[3]);
}

void MotorDrive::Run(int8_t motor1, int8_t motor2, int8_t motor3, int8_t motor4) {
      // Init();
      if (abs(motor1) > 100) motor1 = motor1 * (abs(motor1) / motor1);
      if (abs(motor2) > 100) motor2 = motor2 * (abs(motor2) / motor2);
      if (abs(motor3) > 100) motor3 = motor3 * (abs(motor3) / motor3);
      if (abs(motor4) > 100) motor4 = motor4 * (abs(motor4) / motor4);
      if (motor1 > 0) {
            motor1a_->write(motor1 * 0.01f);
            motor1b_->write(0);
      } else {
            motor1a_->write(0);
            motor1b_->write(motor1 * -0.01f);
      }
      if (motor2 > 0) {
            motor2a_->write(motor2 * 0.01f);
            motor2b_->write(0);
      } else {
            motor2a_->write(0);
            motor2b_->write(motor2 * -0.01f);
      }
      if (motor3 > 0) {
            motor3a_->write(motor3 * 0.01f);
            motor3b_->write(0);
      } else {
            motor3a_->write(0);
            motor3b_->write(motor3 * -0.01f);
      }
      if (motor4 > 0) {
            motor4a_->write(motor4 * 0.01f);
            motor4b_->write(0);
      } else {
            motor4a_->write(0);
            motor4b_->write(motor4 * -0.01f);
      }
}

void MotorDrive::Brake() {
      motor1a_->write(1);
      motor1b_->write(1);
      motor2a_->write(1);
      motor2b_->write(1);
      motor3a_->write(1);
      motor3b_->write(1);
      motor4a_->write(1);
      motor4b_->write(1);
}

void MotorDrive::CheckConnection() {
      // 接続チェック
      motor1a_->sound(700, CHECK_SPEED);
      motor2a_->sound(800, CHECK_SPEED);
      motor3a_->sound(900, CHECK_SPEED);
      motor4a_->sound(1000, CHECK_SPEED);
      motor1b_->sound(700, CHECK_SPEED);
      motor2b_->sound(800, CHECK_SPEED);
      motor3b_->sound(900, CHECK_SPEED);
      motor4b_->sound(1000, CHECK_SPEED);
}