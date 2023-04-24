#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const int btpin = 3; // 버튼
const int mvpin1 = A0; // 가변저항 1
const int mvpin2 = A1; // 가변저항 2
const int mvpin3 = A2; // 가변저항 3

// 버튼 상태
int btstate = 0;
int state = 0;

void setup()
{
  
  Serial.begin(9600); // 시리얼 통신
  
  // 핀 입출력 설정
  pinMode(btpin, INPUT);
  pinMode(mvpin1, INPUT);
  pinMode(mvpin2, INPUT);
  pinMode(mvpin3, INPUT);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  
}

void loop(){
  
  // 가변저항 값 저장
  int sensorInput1 = analogRead(mvpin1);
  sensorInput1 = map(sensorInput1, 0, 1023, 0, 180);
  int sensorInput2 = analogRead(mvpin2);
  sensorInput2 = map(sensorInput2, 0, 1023, 0, 180);
  int sensorInput3 = analogRead(mvpin3);
  sensorInput3 = map(sensorInput3, 0, 1023, 0, 180);
  
  // 가변저항 입력 시 모터 작동
  servo1.write(sensorInput1);
  servo2.write(sensorInput2);
  servo3.write(sensorInput3);
    
  delay(100);
  
  // 버튼 상태 값 저장
  btstate = digitalRead(btpin);
  if(btstate == HIGH){
    if(state == 0){
      state = 1;
    }
    else if(state == 1){
      state = 0;
    }
  }
  
  // 버튼 입력 시 모터 작동
  if(state == 1){
    servo1.write(180);
    delay(650);
    servo1.write(0);
    delay(650);
  }
  else if(state == 0){  
    servo1.write(0);
  }
}