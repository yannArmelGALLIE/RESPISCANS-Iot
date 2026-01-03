#include <Wire.h>
#include "SSD1306Wire.h"

#define SDA_OLED 17
#define SCL_OLED 18
#define RST_OLED 21
#define Vext 36

SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED);

void setup() {
  Serial.begin(115200);
  
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
  delay(100);
  
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, LOW);
  delay(50);
  digitalWrite(RST_OLED, HIGH);
  
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Hello Heltec!");
  display.display();
}

void loop() {
  static int count = 0;
  display.clear();
  display.drawString(0, 20, "Count: " + String(count++));
  display.display();
  delay(1000);
}