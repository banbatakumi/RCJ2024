#include "robot.hpp"

uint16_t adc_get_val[3];

Robot::Robot() {
      catch_front.SetLength(10);
      catch_back.SetLength(10);
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
      serial3.init();
      serial4.init();
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
      motor.CheckConnection();
      HAL_Delay(200);
      dribbler_front.CheckConnection();
      dribbler_back.CheckConnection();
}

void Robot::GetSensors() {
      static float pre_voltage = 9.6;
      info.voltage = adc_get_val[0] * VOLTAGE_CONVERTION;
      info.voltage = info.voltage * (1 - VOLTAGE_RC) + pre_voltage * VOLTAGE_RC;
      pre_voltage = info.voltage;

      catch_front.Compute(adc_get_val[1]);
      catch_back.Compute(adc_get_val[2]);
      info.Catch.front_val = catch_front.Get();
      info.Catch.back_val = catch_back.Get();

      info.Catch.is_front = info.Catch.front_val < CATCH_FRONT_TH ? 1 : 0;
      info.Catch.is_back = info.Catch.back_val < CATCH_BACK_TH ? 1 : 0;
}

void Robot::ImuUart() {
      while (serial1.available()) {
            static const uint8_t HEADER = 0xFF;  // ヘッダ
            static const uint8_t FOOTER = 0xAA;  // ヘッダ
            static const uint8_t dataSize = 6;   // データのサイズ
            static uint8_t index = 0;            // 受信したデータのインデックスカウンター
            static uint8_t recv_data[dataSize];  // 受信したデータ
            static uint8_t recv_byte;

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

void Robot::LineUart() {
      while (serial2.available()) {
            static const uint8_t HEADER = 0xFF;   // ヘッダ
            static const uint8_t FOOTER = 0xAA;   // フッタ
            static const uint8_t data_size = 6;   // データのサイズ
            static uint8_t index = 0;             // 受信したデータのインデックスカウンター
            static uint8_t recv_data[data_size];  // 受信したデータ
            static uint8_t recv_byte;

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
                        info.Line.interval = recv_data[4] >> 4;
                        info.Line.is_on_line = (recv_data[4] >> 3) & 1;
                        info.Line.is_half_out = (recv_data[4] >> 2) & 1;
                        info.Line.is_leftside = (recv_data[4] >> 1) & 1;
                        info.Line.is_rightside = recv_data[4] & 1;
                        info.Line.dir = recv_data[5] * 2 - 180;
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }

      if (line_send_interval_timer.read_us() >= LINE_SEND_PERIOD_US) {
            serial2.write(info.Line.on_led);
            line_send_interval_timer.reset();
      }
}

void Robot::UiUart() {
      static int8_t item;
      static uint8_t sub_item;

      while (serial3.available()) {
            static const uint8_t HEADER = 0xFF;   // ヘッダ
            static const uint8_t FOOTER = 0xAA;   // ヘッダ
            static const uint8_t data_size = 4;   // データのサイズ
            static uint8_t index = 0;             // 受信したデータのインデックスカウンター
            static uint8_t recv_data[data_size];  // 受信したデータ
            static uint8_t recv_byte;

            recv_byte = serial3.read();
            if (index == 0) {
                  if (recv_byte == HEADER) {
                        index++;
                  } else {
                        index = 0;
                  }
            } else if (index == (data_size + 1)) {
                  if (recv_byte == FOOTER) {
                        item = ((recv_data[0] >> 4) & 0b00001111) - 8;
                        sub_item = recv_data[0] & 0b00001111;
                        info.mode = (recv_data[1] >> 4) & 0b00001111;
                        info.Ui.dribbler_sig = (recv_data[1] >> 1) & 0b0000111;
                        info.Ui.set_yaw_zero = recv_data[1] & 0b0000001;
                        info.moving_speed = recv_data[2] * 0.01;
                        info.line_moving_speed = recv_data[3] * 0.01;
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }

      if (info.mode == 0) {
            int16_t debug_val[2];
            debug_val[0] = info.Cam.ball_dir;
            debug_val[1] = info.Cam.ball_dis;

            if (ui_send_interval_timer.read_us() >= UI_SEND_PERIOD_US) {
                  static const uint8_t HEADER = 0xFF;  // ヘッダ
                  static const uint8_t FOOTER = 0xAA;  // ヘッダ
                  if (item == -2) {
                        static const uint8_t data_size = 1;
                        uint8_t send_data[data_size];
                        send_data[0] = info.Catch.is_front << 1 | info.Catch.is_back;
                        serial3.write(send_data, data_size);
                  } else if (item == 0) {
                        static const uint8_t data_size = 10;
                        uint8_t send_data[data_size];
                        send_data[0] = HEADER;
                        send_data[1] = info.voltage * 20;
                        send_data[2] = info.voltage * 0;
                        send_data[3] = (uint8_t)(((uint16_t)(info.Imu.yaw + 32768) & 0xFF00) >> 8);
                        send_data[4] = (uint8_t)((uint16_t)(info.Imu.yaw + 32768) & 0x00FF);
                        send_data[5] = (uint8_t)(((uint16_t)(debug_val[0] + 32768) & 0xFF00) >> 8);
                        send_data[6] = (uint8_t)((uint16_t)(debug_val[0] + 32768) & 0x00FF);
                        send_data[7] = (uint8_t)(((uint16_t)(debug_val[1] + 32768) & 0xFF00) >> 8);
                        send_data[8] = (uint8_t)((uint16_t)(debug_val[1] + 32768) & 0x00FF);
                        send_data[9] = FOOTER;
                        serial3.write(send_data, data_size);
                  } else if (item == 1) {
                        static const uint8_t data_size = 6;
                        uint8_t send_data[data_size];
                        send_data[0] = HEADER;
                        send_data[1] = info.Line.dir;
                        send_data[2] = info.Line.inside_dir;
                        send_data[3] = info.Line.interval;
                        send_data[4] = info.Line.is_on_line << 2 | info.Line.is_leftside << 1 | info.Line.is_rightside;
                        send_data[5] = FOOTER;
                        serial3.write(send_data, data_size);
                  }

                  ui_send_interval_timer.reset();
            }
      }
}

void Robot::CamUart() {
      while (serial4.available()) {
            static const uint8_t HEADER = 0xFF;   // ヘッダ
            static const uint8_t FOOTER = 0xAA;   // フッタ
            static const uint8_t data_size = 11;  // データのサイズ
            static uint8_t index = 0;             // 受信したデータのインデックスカウンター
            static uint8_t recv_data[data_size];  // 受信したデータ
            static uint8_t recv_byte;

            recv_byte = serial4.read();
            if (index == 0) {
                  if (recv_byte == HEADER) {
                        index++;
                  } else {
                        index = 0;
                  }
            } else if (index == (data_size + 1)) {
                  if (recv_byte == FOOTER) {
                        info.Cam.ball_dir = ((((uint16_t)recv_data[0] << 8) & 0xFF00) | ((int16_t)recv_data[1] & 0x00FF)) - 32768;
                        info.Cam.ball_dis = recv_data[2];
                        info.Cam.yellow_goal_dir = recv_data[3] * 2 - 180;
                        info.Cam.yellow_goal_height = recv_data[4];
                        info.Cam.blue_goal_dir = recv_data[5] * 2 - 180;
                        info.Cam.blue_goal_height = recv_data[6];
                        info.Cam.is_goal_front = recv_data[7];
                        info.Cam.own_x = recv_data[8] - 127;
                        info.Cam.own_y = recv_data[9] - 127;
                        info.Cam.proximity[0] = recv_data[10];
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }

      if (cam_send_interval_timer.read_us() >= CAM_SEND_PERIOD_US) {
            serial4.write(info.Imu.yaw * 0.5 + 90);
            cam_send_interval_timer.reset();
      }
}