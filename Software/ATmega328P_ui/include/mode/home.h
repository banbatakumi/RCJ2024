#ifndef _HOME_H_
#define _HOME_H_

#include "setup.h"

#define LOW_VOLTAGE 8
#define HIGH_VOLTAGE 11

int16_t debug_val[2];
int16_t yaw;
float voltage;
bool is_connect_to_ally;
bool is_ally_catch_ball;
bool is_ally_moving;

uint8_t cnt;

void Home() {
      // if (Serial.available() > 0) {
      //       if (Serial.read() == 0xFF) {
      //             uint8_t debug_val_H[2];
      //             uint8_t debug_val_L[2];
      //             uint8_t yaw_H;
      //             uint8_t yaw_L;
      //             uint8_t bool_data;
      //             voltage = Serial.read() / 20.00;
      //             bool_data = Serial.read();
      //             yaw_H = Serial.read();
      //             yaw_L = Serial.read();
      //             debug_val_H[0] = Serial.read();
      //             debug_val_L[0] = Serial.read();
      //             debug_val_H[1] = Serial.read();
      //             debug_val_L[1] = Serial.read();

      //             yaw = ((((uint16_t)yaw_H << 8) & 0xFF00) | ((int16_t)yaw_L & 0x00FF)) - 32768;
      //             for (uint8_t i = 0; i < 2; i++) debug_val[i] = ((((uint16_t)debug_val_H[i] << 8) & 0xFF00) | ((int16_t)debug_val_L[i] & 0x00FF)) - 32768;
      //             is_connect_to_ally = bool_data & 1;
      //             is_ally_moving = (bool_data) >> 1 & 1;
      //             is_ally_catch_ball = (bool_data >> 2) & 1;
      //             is_moving = bool_data >> 3 & 1;
      //             while (Serial.available() > 0) Serial.read();
      //       }
      // }
      static const uint8_t HEADER = 0xFF;   // ヘッダ
      static const uint8_t FOOTER = 0xAA;   // ヘッダ
      static const uint8_t data_size = 8;   // データのサイズ
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
                        voltage = recv_data[0] / 20.00;
                        yaw = ((((uint16_t)recv_data[2] << 8) & 0xFF00) | ((int16_t)recv_data[3] & 0x00FF)) - 32768;
                        debug_val[0] = ((((uint16_t)recv_data[4] << 8) & 0xFF00) | ((int16_t)recv_data[5] & 0x00FF)) - 32768;
                        debug_val[1] = ((((uint16_t)recv_data[6] << 8) & 0xFF00) | ((int16_t)recv_data[7] & 0x00FF)) - 32768;
                  }
                  index = 0;
            } else {
                  recv_data[index - 1] = recv_byte;
                  index++;
            }
      }

      if (mode == 0) {
            oled.setCursor(0, CenterY(5));
            if (voltage > 6) {
                  oled.print("Battery: ");
            } else {
                  oled.print("USB: ");
            }
            oled.print(voltage);
            oled.print("v");
            oled.drawLine(0, 15, 128, 15);

            if (voltage < LOW_VOLTAGE) {
                  for (uint8_t i = 0; i < 16; i++) {
                        led.SetPixelColor(i, 255, 0, 0);
                  }
                  if (sub_item == 1 || sub_item == 2) {
                        oled.drawFrame(13, 42, 102, 15);
                        oled.setCursor(CenterX(64, 11), CenterY(48));
                        oled.print("Can't start");
                  }
            } else if (sub_item == 0) {
                  if (voltage < LOW_VOLTAGE) voltage = LOW_VOLTAGE;
                  if (voltage > HIGH_VOLTAGE) voltage = HIGH_VOLTAGE;
                  for (uint8_t i = 0; i < 16; i++) {
                        led.SetPixelColor(i, 255 * (1 - (float(voltage - LOW_VOLTAGE) / (HIGH_VOLTAGE - LOW_VOLTAGE))), 255 * (float(voltage - LOW_VOLTAGE) / (HIGH_VOLTAGE - LOW_VOLTAGE)), 0);
                  }
            }

            if (is_connect_to_ally) {
                  oled.drawLine(5, 25, 15, 35);
                  oled.drawLine(5, 35, 15, 25);
                  oled.drawLine(10, 20, 10, 40);
                  oled.drawLine(10, 20, 15, 25);
                  oled.drawLine(10, 40, 15, 35);
            }
            if (is_ally_moving) {
                  oled.drawLine(123, 20, 118, 20);
                  oled.drawLine(123, 25, 118, 25);
                  oled.drawLine(123, 30, 118, 30);
                  oled.drawFrame(105, 20, 11, 11);
            }
            if (is_ally_catch_ball) {
                  oled.drawLine(105, 40, 105, 45);
                  oled.drawLine(105, 45, 123, 45);
                  oled.drawLine(123, 40, 123, 45);
                  oled.drawCircle(114, 40, 4);
            }
      }

      if (sub_item == 0) {
            oled.setCursor(CenterX(64, 4), CenterY(32));
            oled.print("Home");
            oled.setCursor(CenterX(64, String(yaw).length()), CenterY(48));
            oled.print(yaw);
            mode = 0;
      } else if (sub_item == 1) {
            if (mode == 0) {
                  oled.setCursor(CenterX(40, 2), CenterY(32));
                  oled.print("OF");
                  oled.setCursor(CenterX(88, 2), CenterY(32));
                  oled.print("DF");
            }
            if (set_val == -1 && voltage > LOW_VOLTAGE) mode = 1;
            if (set_val == 1 && voltage > LOW_VOLTAGE) mode = 2;
            if (pre_sub_item == 0) do_yaw_correction = 1;
            if (do_yaw_correction == 1) cnt++;
            if (cnt > 10) {
                  do_yaw_correction = 0;
                  cnt = 0;
            }
      } else if (sub_item == 2) {
            if (mode == 0) {
                  oled.setCursor(CenterX(64, 7), CenterY(32));
                  oled.print("Control");
            } else {
                  oled.setCursor(0, CenterY(14));
                  oled.print("0: ");
                  oled.print(debug_val[0]);
                  oled.setCursor(0, CenterY(26));
                  oled.print("1: ");
                  oled.print(debug_val[1]);
                  oled.setCursor(0, CenterY(38));
            }
            if (set_val != 0) mode = 3 - mode;
      } else {
            sub_item = 0;
      }
}

#endif