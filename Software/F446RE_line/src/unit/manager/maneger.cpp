#include "maneger.hpp"

uint16_t adc_get_val[12];

Maneger::Maneger() {
}

void Maneger::HardwareInit() {
      HAL_ADC_Start(&hadc1);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_get_val, 12);
      for (uint8_t i = 0; i < 12; i++) {
            while (!(adc_get_val[i] > 0));
      }

      // 諸々の初期化
      serial6.init();
}

void Maneger::GetSensors() {
}
