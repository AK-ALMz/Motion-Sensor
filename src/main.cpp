#include <Arduino.h>
#include <LiquidCrystal.h>
#include <NewPing.h>
#include <Wire.h> //causes errors when not included, not sure why. Maybe #include path problem.
//int setMaxDistance(int, int);

#define PBUTTON 13
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //used default pin layout as in the example code.
const int echoPIN = 11, trigPIN = 12;
int triggerDistance = 50; //Will change it later.
int distance;

NewPing ultrasonic(trigPIN,echoPIN, 100); //max distance 50 CM
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  pinMode(PBUTTON,INPUT);
  delay(50);
  triggerDistance = ultrasonic.ping_cm(); //sets trigger distance
}

void loop() {
  delay(100);
  distance = ultrasonic.ping_cm();
  if(digitalRead(PBUTTON)){ //when PBUTTON pressed, sets the boundary of the motion sensor.
   triggerDistance = distance;
  lcd.print("Target distance:");
  lcd.setCursor(0,1);
  lcd.print("Set to: ");
  lcd.print(triggerDistance);
  delay(1000);
  lcd.clear();
  }
  if (distance < triggerDistance && distance != 0) { //!= 0 since 0 indicates out of max range reading of ultrasonic sensor
  lcd.print("Motion Detect");
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distance);
  delay(1000);
  lcd.clear();
  }
}