#include "robot.hpp"

uint16_t adc_get_val[2];

Robot::Robot() {
}

void Robot::HardwareInit() {
      // HAL_ADC_Start(&hadc1);
      // HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_get_val, 14);
      // for (uint8_t i = 0; i < LINE_QTY; i++) {
      //       while (!(adc_get_val[i] > 0));
      // }

      // 諸々の初期化
      // serial6.init();
      ledh.init();
      motor1a.init();
      motor1b.init();
      motor2a.init();
      motor2b.init();
      motor3a.init();
      motor3b.init();
      motor4a.init();
      motor4b.init();
      dribbler_front_a.init();
      dribbler_front_b.init();
      dribbler_back_a.init();
      dribbler_back_b.init();

      // 接続チェック
      motor1a.sound(700, CHECK_SPEED);
      motor2a.sound(800, CHECK_SPEED);
      motor3a.sound(900, CHECK_SPEED);
      motor4a.sound(1000, CHECK_SPEED);
      motor1b.sound(700, CHECK_SPEED);
      motor2b.sound(800, CHECK_SPEED);
      motor3b.sound(900, CHECK_SPEED);
      motor4b.sound(1000, CHECK_SPEED);
      HAL_Delay(CHECK_SPEED * 2);
      dribbler_front_a.sound(1000, CHECK_SPEED);
      dribbler_front_b.sound(1500, CHECK_SPEED);
      dribbler_back_a.sound(1000, CHECK_SPEED);
      dribbler_back_b.sound(1500, CHECK_SPEED);
}

void Robot::GetSensors() {
}