// letsarduino.com
//  [Project 14] – Servo Motor Controlled Analog Thermometer Using Thermistor (NTC) + Arduino

#include <Servo.h>
#define thermistorPin A0 
int resistorValue = 1000; // resistor value in circuit
Servo myservo;
 
void setup(void)
{
  myservo.attach(11);
  Serial.begin(9600);
}
 
void loop(void) {
  int reading;
 
  //reading = analogRead(thermistorPin);
  reading = (analogRead(thermistorPin)/10)-1;
  reading = resistorValue / reading;
  Serial.print("Celsius :");
  Serial.println(reading);
  
  delay(1000);
  
  int val = (int) reading;
  int temp;
  
  temp = map(val, 0, 49 , 0, 179); // you can chanage degree (0,49)
  
  myservo.write(temp);
  delay(100);
}
