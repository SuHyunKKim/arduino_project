#include <Servo.h>
Servo EduServo1;
Servo EduServo2;


void setup() {
  EduServo1.attach(4);    // 디지털 핀 4번에 연결
  EduServo2.attach(5);
  Serial.begin(9600);
}

void loop() {
  float sensorValue;

  sensorValue = analogRead(A0);
  Serial.print("sensor reading = "); //시리얼 모니터
  Serial.println(sensorValue);

  if(sensorValue >= 1) {
    for (int i=0; i<90; i++){
      EduServo1.write(i); // 0 -> 90
      EduServo2.write(180-i);  //180 -> 90
      delay(50);
    }
    delay(600000);
  }
  else {
    for (int i=90; i>0; i--){
      EduServo1.write(i); // 90 -> 0
      EduServo2.write(180-i); // 90 -> 180
      delay(50);
    }
    delay(600000);
  }
  delay(1000);

}