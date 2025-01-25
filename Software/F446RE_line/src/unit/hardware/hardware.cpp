#include "hardware.hpp"

uint16_t adc_get_val[12];

Hardware::Hardware() {
}

void Hardware::Init() {
      HAL_ADC_Start(&hadc1);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_get_val, 12);
      for (uint8_t i = 0; i < 12; i++) {
            while (!(adc_get_val[i] > 0));
      }

      // 諸々の初期化
      serial6.init();
}

void Hardware::GetSensors() {
      info.Encoder.photo_val[0] = adc_get_val[0];
      info.Encoder.photo_val[1] = adc_get_val[1];
      info.Encoder.photo_val[2] = adc_get_val[2];
      info.Encoder.photo_val[3] = adc_get_val[3];

      info.Line.leftside_val = adc_get_val[4];
      info.Line.rightside_val = adc_get_val[5];
      info.Line.mux1x_val = adc_get_val[6];
      info.Line.mux1y_val = adc_get_val[7];
      info.Line.mux2x_val = adc_get_val[8];
      info.Line.mux2y_val = adc_get_val[9];
      info.Line.mux3x_val = adc_get_val[10];
      info.Line.mux3y_val = adc_get_val[11];
}
