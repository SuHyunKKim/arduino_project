#include <Servo.h>

// 서보 모터 객체 생성
Servo EduServo1;
Servo EduServo2;

// LCD 모니터 라이브러리
#include <Wire.h> //i2c 통신
#include <LiquidCrystal_I2C.h> //LCD 1602 I2C
LiquidCrystal_I2C lcd(0x3F, 16, 2); //접근 주소 : 0x3F or 0x27

// 스위치 핀번호
int flag = 0;


void setup() {
  EduServo1.attach(4);    // 디지털 핀 4번에 연결
  EduServo2.attach(5);

  lcd.begin();
  lcd.backlight();

  Serial.begin(9600);

  // pinMode(A1, INPUT);
}

void loop() {
  float sensorValue;

  sensorValue = analogRead(A0);
  Serial.print("sensor reading = "); //시리얼 모니터
  Serial.println(sensorValue);

  // int data = digitalRead(A1);

  if(sensorValue >= 1) {

    lcd.setCursor(0, 0); 
    lcd.print("UV is strong");
    lcd.setCursor(0, 1); 
    lcd.print("closing shade");

    for (int i=0; i<90; i++){
      EduServo1.write(i); // 0 -> 90
      EduServo2.write(180-i);  //180 -> 90
      delay(50);
    }

    lcd.clear();

    delay(600000);
  }
  else if (sensorValue < 1) {

    lcd.setCursor(0, 0); 
    lcd.print("UV is weak");
    lcd.setCursor(0, 1); 
    lcd.print("opening shade");

    for (int i=90; i>0; i--){
      EduServo1.write(i); // 90 -> 0
      EduServo2.write(180-i); // 90 -> 180
      delay(50);
    }

    lcd.clear();

    delay(600000);
  }

  delay(1000);

}