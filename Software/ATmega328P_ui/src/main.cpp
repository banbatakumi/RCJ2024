#include <Arduino.h>

#include "config.h"

void setup() {
      Serial.begin(38400);  // 通信速度: 9600, 14400, 19200, 28800, 38400, 57600, 115200

      // OLEDセットアップ
      oled.begin();
      oled.setPowerSave(0);
      oled.setFlipMode(1);
      oled.setFont(u8g2_font_courR10_tr);
      oled.firstPage();
      do {
            oled.setCursor(CenterX(64, 12), CenterY(32));
            oled.print("Crescent(Re)");
      } while (oled.nextPage());

      led.SetBrightness(50);
      led.Clear();

      // 起動音
      tone(buzzer_pin, 2000, 100);
      delay(100);
      tone(buzzer_pin, 1000, 100);
      delay(100);
}

void loop() {  // 呼び出しのオーバーヘッド節減
      while (1) {
            ModeRun();
      }
}