int takisti1 = 0;
int takisti2 = 1;
int takisti3 = 2;
int takisti4 = 3;

int takisti1Reading;
int takisti2Reading;
int takisti3Reading;
int takisti4Reading;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  takisti1Reading = analogRead(takisti1);
  takisti2Reading = analogRead(takisti2);
  takisti3Reading = analogRead(takisti3);
  takisti4Reading = analogRead(takisti4);
  Serial.print("Takisti1 = ");
  Serial.print(takisti1Reading);
  Serial.print("  Takisti2 = ");
  Serial.print(takisti2Reading);
  Serial.print("  Takisti3 = ");
  Serial.print(takisti3Reading);
  Serial.print("  Takisti4 = ");
  Serial.print(takisti4Reading);
  
  
  Serial.println("ats");
 
  delay(150);
}
