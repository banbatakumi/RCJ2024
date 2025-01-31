#include "neopixel.h"

NeoPixel::NeoPixel() : led(LED_QTY, 2, NEO_GRB + NEO_KHZ800) {
      led.begin();
}

void NeoPixel::SetPixelColor(int8_t led_num, uint8_t red, uint8_t green, uint8_t blue) {
      int8_t led_num_tmp = 20 - led_num;
      while (led_num_tmp > LED_QTY - 1) led_num_tmp -= LED_QTY;
      while (led_num_tmp < 0) led_num_tmp += LED_QTY;
      led.setPixelColor(led_num_tmp, led.Color(red * (brightness_ / 255.0), green * (brightness_ / 255.0), blue * (brightness_ / 255.0)));
}

void NeoPixel::SetDegree(int16_t degree, bool red, bool green, bool blue) {
      if (degree >= -45 && degree <= 45) {
            degree = SimplifyDeg(degree);
            SetPixelColor(0, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -22.5 && degree <= 67.5) {
            degree = SimplifyDeg(degree - 22.5);
            SetPixelColor(1, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 0 && degree <= 90) {
            degree = SimplifyDeg(degree - 45);
            SetPixelColor(2, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 22.5 && degree <= 112.5) {
            degree = SimplifyDeg(degree - 67.5);
            SetPixelColor(3, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 45 && degree <= 135) {
            degree = SimplifyDeg(degree - 90);
            SetPixelColor(4, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 67.5 && degree <= 157.5) {
            degree = SimplifyDeg(degree - 112.5);
            SetPixelColor(5, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 90 && degree <= 180) {
            degree = SimplifyDeg(degree - 135);
            SetPixelColor(6, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 112.5 || degree <= -157.5) {
            degree = SimplifyDeg(degree - 157.5);
            SetPixelColor(7, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 135 || degree <= -135) {
            degree = SimplifyDeg(degree - 180);
            SetPixelColor(8, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= 157.5 || degree <= -112.5) {
            degree = SimplifyDeg(degree + 157.5);
            SetPixelColor(9, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -180 && degree <= -90) {
            degree = SimplifyDeg(degree + 135);
            SetPixelColor(10, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -157.5 && degree <= -67.5) {
            degree = SimplifyDeg(degree + 112.5);
            SetPixelColor(11, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -135 && degree <= -45) {
            degree = SimplifyDeg(degree + 90);
            SetPixelColor(12, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -112.5 && degree <= -22.5) {
            degree = SimplifyDeg(degree + 67.5);
            SetPixelColor(13, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -90 && degree <= 0) {
            degree = SimplifyDeg(degree + 45);
            SetPixelColor(14, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
      if (degree >= -67.5 && degree <= 22.5) {
            degree = SimplifyDeg(degree + 22.5);
            SetPixelColor(15, (45 - abs(degree)) / 45.0f * brightness_ * red, (45 - abs(degree)) / 45.0f * brightness_ * green, (45 - abs(degree)) / 45.0f * brightness_ * blue);
      }
}

void NeoPixel::SetBrightness(uint8_t brightness) {
      this->brightness_ = brightness;
}

void NeoPixel::Clear() {
      led.clear();
}

void NeoPixel::Show() {
      led.show();
}

void NeoPixel::Rainbow() {
      static int step_num = 0;
      for (int i = 0; i < LED_QTY; i++) {
            // ストリップの長さに沿って色相環（65536の範囲）を1回転させる量だけピクセルの色相をオフセットします。
            int pixelHue = step_num + (i * 65536L / led.numPixels());
            // ColorHSV関数に色相(0 to 65535)を渡し、その結果をgamma32()でガンマ補正します。
            led.setPixelColor(i, led.gamma32(led.ColorHSV(pixelHue)));
      }
      led.show();
      step_num += 256;
      if (step_num == 65536) {
            step_num = 0;
      }
}