/*
  *
  * Udemy.com
  * Building an Arduino DC Voltmeter
  *
  */
 
 float vPow = 5.0;
 float r1 = 100000.0;
 float r2 = 10000.0;
 
 void setup() {
   Serial.begin(9600);
   
   // Send ANSI terminal codes
   //Serial.print("\x1B");
   //Serial.print("[2J");
   //Serial.print("\x1B");
   //Serial.println("[H");
   // End ANSI terminal codes
   
   Serial.println("--------------------");
   Serial.println("DC VOLTMETER");
   Serial.print("Maximum Voltage: ");
   Serial.print((int)(vPow / (r2 / (r1 + r2))));
   Serial.println("V");
   Serial.println("--------------------");
   Serial.println("");
   
   delay(2000);
 }
 
 void loop() {
   float v = (analogRead(0) * vPow) / 1024.0;
   float v2 = v / (r2 / (r1 + r2));
   
   // Send ANSI terminal codes
   //Serial.print("\x1B");
   //Serial.print("[1A");
   // End ANSI terminal codes
   
   Serial.println(v2);
 }
/*
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;
void setup(){
   pinMode(analogInput, INPUT);
   lcd.begin(16, 2);
   lcd.print("DC VOLTMETER");
}
void loop(){
   // read the value at analog input
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;//statement to quash undesired reading !
} 
lcd.setCursor(0, 1);
lcd.print("INPUT V= ");
lcd.print(vin);
delay(500);
}*/
