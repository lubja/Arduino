/* Photocell simple testing sketch.

  Connect one end of the photocell to 5V, the other end to Analog 0.
  Then connect one end of a 10K resistor from Analog 0 to ground
  Connect LED from pin 11 through a resistor to ground
  For more information see http://learn.adafruit.com/photocells */

#include <Servo.h>
#include <math.h>
#include <stdio.h>


Servo myservo;

int photocellPin = A0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider

int photoCellPin2 = A1;
int photoCell2Reading;

int servoPin = 9;
int servoFuturePos;

int suund;
int currentPos;


int delta;
int lightPos;

int delta_max = 0;

int step_value;

int pc1_start;
int pc2_max;
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
  myservo.attach(9);

  while (millis() < 5000) { //calibration
    photocellReading = analogRead(photocellPin);
    photoCell2Reading = analogRead(photoCellPin2);

    int    current_min = abs(photocellReading - photoCell2Reading);
    if (current_min > delta_max) {
      delta_max = current_min;
    }
  }
  Serial.print("Max delta: ");
  Serial.println(delta_max);
  //divide delta_max with 36
  //then we have the number we need for each step aka lets say the number is 10
  //this means that for each difference of 10 in photocell values the servo motor moves 5 degrees.
  step_value = round(delta_max / 36);
  pc1_start = round(delta_max / 2) * (-1);
  pc2_max = round(delta_max / 2); //dividing with 2 is probably unnecessary and wrong


  Serial.print("Step value: ");
  Serial.println(step_value);
}

void loop(void) {




  //if photocell1 - photocell2<0 then the light is stronger towards photocell2
  // else light is stronger near photocell1

  photocellReading = analogRead(photocellPin);
  photoCell2Reading = analogRead(photoCellPin2);

  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
  Serial.print("LDR2 reading = ");
  Serial.println(photoCell2Reading);


  delta = photocellReading - photoCell2Reading;
  Serial.print("Delta reading = ");
  Serial.println(delta);
  if (abs(delta) >= step_value) { //useless to move motor and calculate if the difference in values is too small

    if (delta < 0) {
      Serial.println("MOVE TOWARDS PHOTOCELL2.");

      servoFuturePos  = 90 + 5 * round(abs(delta) / step_value);
      if (servoFuturePos > 179) {
        servoFuturePos = 179;// don\t go too high
      }
    }
    else {
      Serial.println("FORWARDS TO PHOTOCELL1.");
      servoFuturePos = 90 - 5 * round(delta / step_value);
      if (servoFuturePos < 0) {
        servoFuturePos = 0; //don't go too low
      }
    }



    Serial.println(servoFuturePos);
    currentPos = myservo.read();
    if (servoFuturePos < currentPos) { //determine the direction that the motor should move to
      suund = -1;
    }
    else {
      suund = 1;
    }
    for (currentPos; currentPos != servoFuturePos; currentPos += suund) {
      myservo.write(currentPos);
      delay(15);

    }


  }
  else {
    Serial.println("-------------------------------------Too small delta----------------------------------");
  }

  delay(1000);


  /*
    if(photocellReading > photoCell2Reading){
      servoFuturePos = 1;
    }
    else{
      servoFuturePos = 178;
    }
    delta  = photocellReading - photoCell2Reading;


    Serial.print("Delta and lightPos :");
    Serial.println(delta);
    Serial.println(lightPos);




    if(lightPos > myservo.read()){
      suund = 1;
    }
    else{
      suund = -1;
    }
     Serial.print("Servo pos: ");
    Serial.println(myservo.read());

    Serial.print("Servo future pos ");
    Serial.println(servoFuturePos);



    currentPos = myservo.read();
    for(currentPos;currentPos != lightPos ;currentPos += suund){
      myservo.write(currentPos);

    }


    delay(1500);
  */
}


