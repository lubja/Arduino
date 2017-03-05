#include <Servo.h>
#include <math.h>
#include <SPI.h>
#include <SD.h>

const int sd_card = 10;

int upperRight = A0; // Pin of upperRight LDR
int upperRightReading; // upperRight LDR's value

int bottomRight = A5;
int bottomRightReading;

int upperLeft = A3;
int upperLeftReading; 

int lowerLeft = A2;
int lowerLeftReading;

int solar_cell = A1;
double cellReading;

Servo horizontal; //servo that controls horizontal movement - 0 -> 90 = to the left, 90-> 0 = to the right
Servo vertical; // servo that controls vertical movement - 0 ->  90 = "higher", 90 -> 0 = "lower"

int horizontal_servo = 9;// Pin of servo that controls horizontal movement
int horizontal_current; // Current position of horizontal servo

int vertical_servo = 8; // Pin of servo that controls vertical movement
int vertical_current; // Current position of vertical servo

int upper_average; // (upperRight + upperLeft) / 2
int lower_average;
int left_average; // (upperLeft + lowerLeft)/2
int right_average;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  horizontal.attach(horizontal_servo);
  vertical.attach(vertical_servo);
  SD.begin(sd_card);
}

void loop() {
  // put your main code here, to run repeatedly:
  upperRightReading = analogRead(upperRight);
  bottomRightReading = analogRead(bottomRight);
  upperLeftReading = analogRead(upperLeft);
  lowerLeftReading = analogRead(lowerLeft);
  Serial.print("Upper right: ");
  Serial.print(upperRightReading);

  Serial.print("    Bottom right: ");
  Serial.print(bottomRightReading);

  Serial.print("   Upper left LDR: ");
  Serial.print(upperLeftReading);

  Serial.print("   Lower left LDR: ");
  Serial.println(lowerLeftReading);
  cellReading = analogRead(solar_cell);
  float voltage = cellReading * 5 / 1023;
  Serial.print("Solar cell element voltage : ");
  Serial.println(voltage);

  upper_average = round((upperRightReading + upperLeftReading)/2);
  lower_average = round((lowerLeftReading + bottomRightReading)/2);

  horizontal_current = horizontal.read();
  vertical_current = vertical.read();

  
  if(upper_average > lower_average && vertical_current < 90){ // reposition the vertical motor
    vertical.write(vertical_current +1);
    Serial.println("Moving 'higher'");
  }
  else if(lower_average > upper_average && vertical_current >0){
    vertical.write(vertical_current -1);
    Serial.println("Moving 'lower'");
  }

  left_average = round((upperLeftReading + lowerLeftReading)/2);
  right_average = round((upperRightReading + bottomRightReading)/2);

  if(left_average>right_average && horizontal_current < 90){
    horizontal.write(horizontal_current + 1);
    Serial.println("Moving to the left");
  }
  else if(right_average > left_average && horizontal_current > 0 ){
    horizontal.write(horizontal_current -1);
    Serial.println("Moving to the right");
  }
  if(millis() % 6000 > 5900){ // LETS LOG EVERY OTHER 6 SECONDS
    Serial.println("LOGGING NOW!!!!!!!!!!!!!!!!!!!!!");
    File dataFile = SD.open("solar.txt", FILE_WRITE);

    if(dataFile){
      dataFile.println(voltage);
      dataFile.close();
    }
    else{
      Serial.println("COULD NOT LOG FOR SOME REASON!!!!!! LOOK INTO IT ASAP");
    }
    
  }
 // Serial.println(millis() % 6000);
  delay(100);
}
