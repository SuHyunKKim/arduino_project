#include <Servo.h> 
Servo servo;     
 
void setup() { 
  servo.attach(10);  
} 
 
void loop() { 
  int val=0;
  val = analogRead(0);             
  val = map(val, 0, 1023, 0, 179); //아날로그 값(0-1023)을 서보 값(0-179)으로 매핑     
  servo.write(val); //각도에 따라 서보 회전
  delay(10);                           
}



#include <Servo.h>
Servo EduServo;
                         // 서보 모터의 각도 조절 변수

void setup() {
  EduServo.attach(4);    // 디지털 핀 4번에 연결
}

void loop() {
  EduServo.write(0);
  delay(1000);
  EduServo.write(90);
  delay(1000);
  EduServo.write(180);
  delay(1000);

  // exit(0);           // 종료 코드
}


#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(13);
}

void loop() {
  myservo.write(90);
  delay(1000);
  myservo.write(180);
  delay(1000);
}
