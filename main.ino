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
int flag2 = 0;


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

  int data = digitalRead(A1);

  if(sensorValue >= 1) { // 자외선 수치 1 이상일때는 자동으로 닫음

    lcd.setCursor(0, 0); 
    lcd.print("UV is strong");
    lcd.setCursor(0, 1); 
    lcd.print("closing shade");

    for (int i=0; i<100; i++){
      EduServo1.write(i); // 0 -> 90
      EduServo2.write(180-i);  //180 -> 90
      delay(50);
    }

    lcd.clear();

    d = 0;
    while (d<600)  { // 컨셉 : 매초 스위치 값을 10분동안 읽으면서 스위치 값이 바뀌면 수동으로 다시 열음
      int dataIn = digitalRead(A1);
      delay(1000);
      d += 1;
      if (flag != dataIn) {
        flag = dataIn;

        lcd.setCursor(0, 0); 
        lcd.print("Opening shade");
        lcd.setCursor(0, 1); 
        lcd.print("manually");  

        for (int i=100; i>0; i--){
          EduServo1.write(i); // 90 -> 0
          EduServo2.write(180-i); // 90 -> 180
          delay(50);
        }

        lcd.clear(); 
      }
    }
  }
  else if (sensorValue < 1) { // 자외선 수치 1 미만일때는 자동으로 열음

    lcd.setCursor(0, 0); 
    lcd.print("UV is weak");
    lcd.setCursor(0, 1); 
    lcd.print("opening shade");

    for (int i=100; i>0; i--){
      EduServo1.write(i); // 90 -> 0
      EduServo2.write(180-i); // 90 -> 180
      delay(50);
    }

    lcd.clear();

    d = 0;
    while (d<600)  { // 컨셉 : 매초 스위치 값을 10분동안 읽으면서 스위치 값이 바뀌면 수동으로 다시 닫음
      int dataIn = digitalRead(A1);
      delay(1000);
      d += 1;
      if (flag != dataIn) {
        flag = dataIn;

        lcd.setCursor(0, 0); 
        lcd.print("Closing shade");
        lcd.setCursor(0, 1); 
        lcd.print("manually");   

        for (int i=0; i<100; i++){
          EduServo1.write(i); // 0 -> 90
          EduServo2.write(180-i);  //180 -> 90
          delay(50);
        }
        
        lcd.clear(); 
      }
    }
  }

  else if (flag != data) { // 수동으로 여닫는 기능
    if (flag2 % 2 == 0) { // flag2가 짝수일떄는 수동으로 닫음
      flag = data;
      flag2 += 1;

      lcd.setCursor(0, 0); 
      lcd.print("Closing shade");
      lcd.setCursor(0, 1); 
      lcd.print("manually");

      for (int i=0; i<100; i++){
        EduServo1.write(i); // 0 -> 90
        EduServo2.write(180-i);  //180 -> 90
        delay(50);
      } 
          
      lcd.clear();
    }
    else { // flag2가 홀수일때는 수동으로 열음
      flag = data;
      flag2 += 1;

      lcd.setCursor(0, 0); 
      lcd.print("Opening shade");
      lcd.setCursor(0, 1); 
      lcd.print("manually");

      for (int i=100; i>0; i--){
        EduServo1.write(i); // 90 -> 0
        EduServo2.write(180-i); // 90 -> 180
        delay(50);
      }

      lcd.clear(); 
    }
    delay(60000); // 수동으로 여닫았을때는 딜레이 1분으로 설정. 자외선이 1분뒤에 엄청쎄면 닫아주려고.
  }

  delay(1000);

}