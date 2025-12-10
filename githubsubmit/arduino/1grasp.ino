#include <Servo.h>

Servo gripServo;   // 그리퍼 서보 1개

void setup() {
  Serial.begin(115200);   // 노트북과 시리얼 통신 속도

  gripServo.attach(10);   // D10 핀에 서보 신호선 연결
  gripServo.write(10);     // 초기: 벌어진 상태(10도)

  Serial.println("Ready: send angle like 0~60");
}

void loop() {
  if (Serial.available()) {
    // 노트북에서 "30\n" 이런 식으로 보낸다고 가정
    String line = Serial.readStringUntil('\n');
    line.trim();  // 앞뒤 공백 제거

    int angle = line.toInt();        // 문자열 -> 정수
    angle = constrain(angle, 10, 70); // 안전하게 10~70 제한

    gripServo.write(angle);          // 서보 회전

    Serial.print("Set angle: ");
    Serial.println(angle);
  }
}
