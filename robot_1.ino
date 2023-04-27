#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const int btpin = 3; // 버튼
const int mvpin1 = A0; // 가변저항 1
const int mvpin2 = A1; // 가변저항 2

// 버튼 상태
int btstate = 0;
int state = 0;

// 버튼 상태 값 저장
void btst(){
  btstate = digitalRead(btpin);
  if(btstate == HIGH){
    if(state == 0){
      state = 1;
    }
    else if(state == 1){
      state = 0;
    }
  }
}

void setup()
{
  
  Serial.begin(9600); // 시리얼 통신
  
  // 핀 입출력 설정
  pinMode(btpin, INPUT);
  pinMode(mvpin1, INPUT);
  pinMode(mvpin2, INPUT);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);

  // 버튼 인터럽트
  attachInterrupt(1, btst, RISING);
  
}

void loop(){
  // 시리얼 통신
  String input;
  if(Serial.available()){
    input = Serial.readStringUntil('\n');
    if(input.equals("ON")){
      servo1.write(90);
      delay(1000);
      servo3.write(90);
      delay(1000);
    }
    else if(input.equals("OFF")){
      servo1.write(0);
      delay(1000);
      servo3.write(0);
      delay(1000);
    }
  }

  // 가변저항 값 저장
  int sensorInput1 = analogRead(mvpin1);
  sensorInput1 = map(sensorInput1, 0, 1023, 0, 180);
  int sensorInput2 = analogRead(mvpin2);
  sensorInput2 = map(sensorInput2, 0, 1023, 0, 180);
  
  // 가변저항 입력 시 모터 작동
  servo1.write(sensorInput1);
  servo2.write(sensorInput2);
    
  delay(100);
  
  
  // 버튼 입력 시 모터 작동
  if(state == 1){
    servo3.write(90);
    delay(300);
    servo3.write(0); 
    delay(300);
  }
  else if(state == 0){  
    servo3.write(0);
  }
}