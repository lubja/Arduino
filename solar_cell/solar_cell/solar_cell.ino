int solar_cell = A3;
double solar_voltage;
double voltage;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  solar_voltage = analogRead(solar_cell);
  voltage = (solar_voltage/1023)*5;
  Serial.print("N2it on: ");
  Serial.println(voltage );
  delay(350);
}

//v]iks olla 10mA, ytleme, et full poweri juues on 3V
// I = U/R => R= U/I => R= 300ohm
