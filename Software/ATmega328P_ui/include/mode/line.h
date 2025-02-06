#ifndef _LINE_H_
#define _LINE_H_

#include "setup.h"

int16_t line_dir;
int16_t line_inside_dir;
uint8_t line_interval;
bool is_on_line;
bool is_leftside;
bool is_rightside;

void Line() {
      // if (Serial.available() > 0) {
      //       if (Serial.read() == 0xFF) {
      //             uint8_t bool_data;
      //             line_dir = Serial.read() * 2 - 180;
      //             line_inside_dir = Serial.read() * 2 - 180;
      //             line_interval = Serial.read();
      //             bool_data = Serial.read();
      //             is_on_line = (bool_data >> 2) & 1;
      //             is_left_line = (bool_data >> 1) & 1;
      //             is_right_line = bool_data & 1;

      //             while (Serial.available() > 0) Serial.read();
      //       }
      // }
      static const uint8_t HEADER = 0xFF;   // ヘッダ
      static const uint8_t FOOTER = 0xAA;   // ヘッダ
      static const uint8_t data_size = 4;   // データのサイズ
      static uint8_t index = 0;             // 受信したデータのインデックスカウンター
      static uint8_t recv_data[data_size];  // 受信したデータ
      static uint8_t recv_byte;
      while (Serial.available()) {
            recv_byte = Serial.read();
            if (index == 0) {
                  if (recv_byte == HEADER) {
                        index++;
                  } else {
                        index = 0;
                  }
            } else if (index == (data_size + 1)) {
                  if (recv_byte == FOOTER) {
                        line_dir = recv_data[0] * 2 - 180;
                        line_inside_dir = recv_data[1] * 2 - 180;
                        line_interval = recv_data[2];
                        is_on_line = (recv_data[3] >> 2) & 1;
                        is_leftside = (recv_data[3] >> 1) & 1;
                        is_rightside = recv_data[3] & 1;
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }

      if (sub_item == 0) {
            oled.setCursor(CenterX(64, 4), CenterY(32));
            oled.print("Line");
      } else if (sub_item == 1) {
            oled.setCursor(0, CenterY(20));
            oled.print("Dir: ");
            oled.print(line_dir);
            oled.setCursor(0, CenterY(32));
            oled.print("Inside: ");
            oled.print(line_inside_dir);
            oled.setCursor(0, CenterY(44));
            oled.print("Interval: ");
            oled.print(line_interval);
      } else {
            sub_item = 0;
      }

      if (is_on_line == 1) led.SetDegree(line_inside_dir, 0, 1, 0);
      if (is_leftside) led.SetPixelColor(12, 0, 0, 255);
      if (is_rightside) led.SetPixelColor(4, 0, 0, 255);
}

#endif