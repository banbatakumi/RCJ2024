#include "motor_drive.hpp"

int debug;

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b,
                       PwmSingleOut *motor2a, PwmSingleOut *motor2b,
                       PwmSingleOut *motor3a, PwmSingleOut *motor3b,
                       PwmSingleOut *motor4a, PwmSingleOut *motor4b,
                       int16_t *yaw, uint8_t *motor_rps)
    : motor1a_(motor1a), motor1b_(motor1b), motor2a_(motor2a), motor2b_(motor2b), motor3a_(motor3a), motor3b_(motor3b), motor4a_(motor4a), motor4b_(motor4b) {
      this->yaw_ = yaw;
      this->motor_rps_ = motor_rps;
      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            motor_ave[i].SetLength(MOVING_AVE_NUM);
            motor_pid[i].SetGain(10, 15, 0.1);
            motor_pid[i].SetLimit(MIN_POWER, MAX_POWER);
            motor_pid[i].SetSamplingFreq(1000);
            motor_pid[i].SetType(1);
      }

      pid.SetGain(3, 0, 0.3);
      pid.SetLimit(-150, 150);
      pid.SetSamplingFreq(500);
      pid.SetType(0);
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

#define WHEEL_R 0.025

void MotorDrive::Drive(int16_t deg, float speed) {
      int16_t power[MOTOR_QTY];
      float vel_x, vel_y;

      vel_x = speed * MyMath::cosDeg(deg);
      vel_y = speed * MyMath::sinDeg(deg);

      pid.Compute(0, *yaw_);
      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            power[i] = (1 / 0.025) * (-1 * MyMath::sinDeg(45 + (90 * i)) * MyMath::cosDeg(45) * vel_x + MyMath::cosDeg(45 + (90 * i)) * MyMath::cosDeg(45) * vel_y) * PI * 2;
            power[i] -= pid.Get();
            // power[i] = MyMath::sinDeg(deg - (45 + (90 * i))) * speed;
      }

      // PIDで姿勢制御

      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            motor_pid[i].Compute(motor_rps_[i], abs(power[i]));
            if (power[i] > 0) {
                  power[i] = motor_pid[i].Get();
            } else {
                  power[i] = motor_pid[i].Get() * -1;
            }
      }
      // 移動平均
      for (uint8_t i = 0; i < MOTOR_QTY; i++) {
            motor_ave[i].Compute(power[i]);
            power[i] = motor_ave[i].Get();
      }

      Run(power[0], power[1], power[2], power[3]);
}

void MotorDrive::Run(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4) {
      // Init();
      if (abs(motor1) > 1000) motor1 = motor1 * (abs(motor1) / motor1);
      if (abs(motor2) > 1000) motor2 = motor2 * (abs(motor2) / motor2);
      if (abs(motor3) > 1000) motor3 = motor3 * (abs(motor3) / motor3);
      if (abs(motor4) > 1000) motor4 = motor4 * (abs(motor4) / motor4);
      if (motor1 > 0) {
            motor1a_->write(motor1 * 0.001f);
            motor1b_->write(0);
      } else {
            motor1a_->write(0);
            motor1b_->write(motor1 * -0.001f);
      }
      if (motor2 > 0) {
            motor2a_->write(motor2 * 0.001f);
            motor2b_->write(0);
      } else {
            motor2a_->write(0);
            motor2b_->write(motor2 * -0.001f);
      }
      if (motor3 > 0) {
            motor3a_->write(motor3 * 0.001f);
            motor3b_->write(0);
      } else {
            motor3a_->write(0);
            motor3b_->write(motor3 * -0.001f);
      }
      if (motor4 > 0) {
            motor4a_->write(motor4 * 0.001f);
            motor4b_->write(0);
      } else {
            motor4a_->write(0);
            motor4b_->write(motor4 * -0.001f);
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