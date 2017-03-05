#include <Servo.h>

Servo myservo;

int currentPos;
int suund;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  currentPos = myservo.read();

  Serial.print("servo asend: ");
  Serial.println(currentPos);
  int pos = currentPos;
  if(currentPos>90){
    suund = -1;
  }
  else{
    suund = 1;
  }

  

  for(pos; pos != 89;pos += suund){
    myservo.write(pos);
    delay(15);
  }

  delay(350);
}
