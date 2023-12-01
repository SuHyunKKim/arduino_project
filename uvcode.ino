#include <Wire.h> //i2c 통신
#include <LiquidCrystal_I2C.h> //LCD 1602 I2C
LiquidCrystal_I2C lcd(0x3F, 16, 2); //접근 주소 : 0x3F or 0x27

#include <Servo.h>
Servo EduServo;

float sensorCriteria1 = 1;
float sensorCriteria2 = 2; //가장 자외선 수치가 클 때

int isOpen = 0; //유모차 가림막이 펼쳐져 있는 상태임을 표시한다.
//(펼쳐지지 않은 상태 : 0, 반만 펼쳤을 때 : 1, 전부 펼쳤을 때 : 2)
int flag = 5; //유모차 가림막을 움직인 후 5초동안은 움직이지 않게 하기 위해 사용


void setup() {
  lcd.begin(); //LCD초기화
  lcd.backlight();

  EduServo.attach(4);    // 디지털 핀 4번에 연결
  Serial.begin(9600);
}

void loop() {
  float sensorValue;
 
  sensorValue = analogRead(A0);
  Serial.print("sensor reading = "); //시리얼 모니터
  Serial.println(sensorValue);

  if(flag >= 5){ 
    if ((isOpen == 0 && sensorValue >= sensorCriteria2) || (isOpen == 1 && sensorValue >= sensorCriteria2)) {
      EduServo.write(60); //가장 많이 펼치는 각도

      lcd.setCursor(0, 0);
      lcd.print("shade open");

			isOpen = 2;
    }
    else if((isOpen == 0 && sensorValue >= sensorCriteria1) || (isOpen == 2 && sensorValue >= sensorCriteria1 && sensorValue <= sensorCriteria2)) {
      EduServo.write(30); //두번째

      lcd.setCursor(0, 0);
      lcd.print("shade open");

			isOpen = 1;
    }
    else if(isOpen != 0 && sensorValue < sensorCriteria1){
      EduServo.write(0);

      lcd.setCursor(0, 0);
      lcd.print("shade down");

			isOpen = 0;
    }
		else{ 
			break; 
		}

    flag = 0;
  }
  else if(flag == 3){ //3초 후 lcd 디스플레이어 초기화
    lcd.clear();
    flag++;
  }
  else{
    flag++;
  }

  delay(1000);    

}