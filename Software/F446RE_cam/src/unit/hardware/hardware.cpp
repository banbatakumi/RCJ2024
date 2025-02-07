#include "hardware.hpp"

Hardware::Hardware() {
}

void Hardware::Init() {
      // 諸々の初期化
      serial1.init();
      serial2.init();
      serial3.init();
      serial5.init();
      serial6.init();
      led1.init();
      led2.init();
      led3.init();
      led4.init();
}

void Hardware::MainUart() {
      while (serial3.available()) info.yaw = serial3.read();

      if (main_send_interval_timer.read_us() >= MAIN_SEND_PERIOD_US) {
            static const uint8_t HEADER = 0xFF;  // ヘッダ
            static const uint8_t FOOTER = 0xAA;  // ヘッダ

            static const uint8_t data_size = 13;
            uint8_t send_data[data_size];
            send_data[0] = HEADER;
            send_data[1] = (uint8_t)(((uint16_t)(info.ball_dir + 32768) & 0xFF00) >> 8);
            send_data[2] = (uint8_t)((uint16_t)(info.ball_dir + 32768) & 0x00FF);
            send_data[3] = info.ball_dis;
            send_data[4] = info.yellow_goal_dir * 0.5 + 90;
            send_data[5] = info.yellow_goal_height * 0.5 + 90;
            send_data[6] = info.blue_goal_dir * 0.5 + 90;
            send_data[7] = info.blue_goal_height * 0.5 + 90;
            send_data[8] = info.is_goal_front;
            send_data[9] = info.own_x + 127;
            send_data[10] = info.own_y + 127;
            send_data[11] = info.Cam[0].proximity;
            send_data[12] = FOOTER;
            serial3.write(send_data, data_size);

            main_send_interval_timer.reset();
      }
}