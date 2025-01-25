#include "robot.hpp"

uint16_t adc_get_val[3];

Robot::Robot() {
}

void Robot::HardwareInit() {
      HAL_ADC_Start(&hadc1);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_get_val, 3);
      for (uint8_t i = 0; i < 3; i++) {
            while (!(adc_get_val[i] > 0));
      }

      // 諸々の初期化
      serial1.init();
      serial2.init();
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

      // 接続確認
      // motor.CheckConnection();
      // HAL_Delay(200);
      // dribbler_front.CheckConnection();
      // dribbler_back.CheckConnection();
}

void Robot::GetSensors() {
      const float voltage_conversion = 0.01298828125;
      info.voltage = adc_get_val[0] * voltage_conversion;
}

void Robot::RecvImuUart() {
      static const uint8_t HEADER = 0xFF;  // ヘッダ
      static const uint8_t FOOTER = 0xAA;  // ヘッダ
      static const uint8_t dataSize = 6;   // データのサイズ
      static uint8_t index = 0;            // 受信したデータのインデックスカウンター
      static uint8_t recv_data[dataSize];  // 受信したデータ
      static uint8_t recv_byte;

      while (serial1.available()) {
            recv_byte = serial1.read();
            if (index == 0) {
                  if (recv_byte == HEADER) {
                        index++;
                  } else {
                        index = 0;
                  }
            } else if (index == (dataSize + 1)) {
                  if (recv_byte == FOOTER) {
                        info.Imu.yaw = ((((uint16_t)recv_data[0] << 8) & 0xFF00) | ((int16_t)recv_data[1] & 0x00FF)) * 0.1 - 180;
                        info.Imu.pitch = ((((uint16_t)recv_data[2] << 8) & 0xFF00) | ((int16_t)recv_data[3] & 0x00FF)) * 0.1 - 180;
                        info.Imu.roll = ((((uint16_t)recv_data[4] << 8) & 0xFF00) | ((int16_t)recv_data[5] & 0x00FF)) * 0.1 - 180;
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }
}

void Robot::RecvLineUart() {
      static const uint8_t HEADER = 0xFF;   // ヘッダ
      static const uint8_t FOOTER = 0xAA;   // ヘッダ
      static const uint8_t data_size = 4;   // データのサイズ
      static uint8_t index = 0;             // 受信したデータのインデックスカウンター
      static uint8_t recv_data[data_size];  // 受信したデータ
      static uint8_t recv_byte;
      serial2.write(info.Line.on_led);

      while (serial2.available()) {
            recv_byte = serial2.read();
            if (index == 0) {
                  if (recv_byte == HEADER) {
                        index++;
                  } else {
                        index = 0;
                  }
            } else if (index == (data_size + 1)) {
                  if (recv_byte == FOOTER) {
                        info.motor_rps[0] = recv_data[0];
                        info.motor_rps[1] = recv_data[1];
                        info.motor_rps[2] = recv_data[2];
                        info.motor_rps[3] = recv_data[3];
                        // info.Line.interval = recv_data[2];
                        // info.Line.is_on_line = (recv_data[3] >> 2) & 1;
                        // info.Line.is_leftside = (recv_data[3] >> 1) & 1;
                        // info.Line.is_rightside = recv_data[3] & 1;
                        // info.Line.dir = recv_data[4] * 2 - 180;
                        // info.Line.inside_dir = recv_data[5] * 2 - 180;
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
            led1 = 1;
      }
}