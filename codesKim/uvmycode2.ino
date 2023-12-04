// 모터 라이브러리
#include <Servo.h>
Servo servo;

// LCD 모니터 라이브러리
#include <Wire.h> //i2c 통신
#include <LiquidCrystal_I2C.h> //LCD 1602 I2C
LiquidCrystal_I2C lcd(0x3F, 16, 2); //접근 주소 : 0x3F or 0x27

// 자외선 센서 라이브러리


float UVcriteria = 1; // 덮개 작동하는 자외선 수치 기준
int cover = 0; //덮개 상태 (0: 열림, 1: 닫힘)
float sensorValue; // 자외선 값 저장할 변수
int flag2 = false;

void setup() {
    lcd.begin(); //LCD초기화
    lcd.backlight();

    servo.attach(4);    // 디지털 핀 4번에 연결
    Serial.begin(9600); // 시리얼 통신 시작
}

void loop() {
    float sensorValue;

    sensorValue = analogRead(A0);
    Serial.print("sensor reading = ");
    Serial.println(sensorValue);

    if (sensorValue >= UVcriteria) { // 자외선 값이 기준치보다 크거나 같으면
        // cover 변수 닫힘으로 변경
        cover = 1;
        flag2 = true;
        // LCD
        lcd.setCursor(0, 0); // 첫번째 즐
        lcd.print("UV is strong");
        lcd.setCursor(0, 1); // 두번째 줄
        lcd.print("closing shade");
        // delay time
        delay(3000); // 3초 대기
        lcd.clear(); // LCD 화면 지우기
        // motor
        servo.write(120); // 덮개를 닫는다.
    } 
    else { // 자외선 값이 기준치보다 작으면
        // cover 변수 열림으로 변경
        cover = 0;
        flag2 = true;
        // LCD
        lcd.setCursor(0, 0); // 첫번째 줄
        lcd.print("UV is weak");
        lcd.setCursor(0, 1); // 두번째 줄
        lcd.print("opening shade");
        // delay time
        delay(3000); // 3초 대기
        lcd.clear(); // LCD 화면 지우기
        // motor
        servo.write(0); // 덮개를 연다.
    }

    if (flag2 == true){
        delay(600000); // 10분 대기
        flag2 = false;
    }
    else {
        delay(1000); // 1초 대기
    }
}