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
      LedH.init();
      Motor1A.init();
      Motor1B.init();
      Motor2A.init();
      Motor2B.init();
      Motor3A.init();
      Motor3B.init();
      Motor4A.init();
      Motor4B.init();
      DribblerFrontA.init();
      DribblerFrontB.init();
      DribblerBackA.init();
      DribblerBackB.init();
}

void Robot::GetSensors() {
}