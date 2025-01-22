#include "robot.hpp"

uint16_t adc_get_val[2];

Robot::Robot() {
}

void Robot::hardwareInit() {
      // HAL_ADC_Start(&hadc1);
      // HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_get_val, 14);
      // for (uint8_t i = 0; i < LINE_QTY; i++) {
      //       while (!(adc_get_val[i] > 0));
      // }

      // 諸々の初期化
      // serial6.init();
      motor1a.init();
      motor1b.init();
}

void Robot::getSensors() {
}

void Robot::LineCompute() {
}