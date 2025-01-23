#include "dribbler_drive.hpp"

DribblerDrive::DribblerDrive(PwmSingleOut *motor_a, PwmSingleOut *motor_b)
    : motor_a_(motor_a), motor_b_(motor_b) {
      ave.SetLength(MOVING_AVE_NUM);
}

void DribblerDrive::Init() {
      motor_a_->init();
      motor_b_->init();
}

void DribblerDrive::Hold(uint8_t power) {
      motor_a_->write(power * 0.01f);
      motor_b_->write(0);
}

void DribblerDrive::Kick() {
      motor_a_->write(0);
      motor_b_->write(1);
}

void DribblerDrive::Brake() {
      motor_a_->write(1);
      motor_b_->write(1);
}

void DribblerDrive::CheckConnection() {
      // 接続チェック
      motor_a_->sound(1000, CHECK_SPEED);
      motor_b_->sound(1500, CHECK_SPEED);
}