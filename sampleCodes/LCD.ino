#include <Wire.h>                                  // i2c 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>                     // LCD 1602 I2C용 라이브러리
LiquidCrystal_I2C lcd(0x27, 16, 2);                // 접근 주소 : 0x3F or 0x27

void setup() {
  lcd.begin();                                    // LCD 초기화
  //Print a message to the LCD.
  lcd.backlight();                               // 백라이트 켜기
  lcd.setCursor(0, 0);                               // 1번 칸, 1번 줄
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);                             // 1번 칸, 2번 줄
  lcd.print("Enjoy - Eduino");
}

void loop() {
}
