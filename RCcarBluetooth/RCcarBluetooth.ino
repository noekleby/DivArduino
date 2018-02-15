/*
 * created by Rui Santos, http://randomnerdtutorials.wordpress.com
 * Modified by Magnus Nokleby Pedersen (inc).
 * Control DC motor with Smartphone via bluetooth
 * 2013
 */
volatile int gear = 150; //default speed First Gir
byte motorPin11 = 3; // pin 2 on L293D IC
byte motorPin21 = 5; // pin 7 on L293D IC
byte enablePin1 = 6; // pin 1 on L293D IC
byte motorPin12 = 9; // Speilvendt av motor 1
byte motorPin22 = 10; // -||-
byte enablePin2 = 11; // -||-
volatile char state; //variable to receive data
byte flag = 0;        //makes sure that the serial only prints once the state

void setup() {
    // sets the pins as outputs:
    pinMode(motorPin11, OUTPUT);
    pinMode(motorPin21, OUTPUT);
    pinMode(enablePin1, OUTPUT);
    pinMode(motorPin12, OUTPUT);
    pinMode(motorPin22, OUTPUT);
    pinMode(enablePin2, OUTPUT);
    Help();
    // sets enablePin high so that motor can turn on:
    //digitalWrite(enablePin1, HIGH);
    //digitalWrite(enablePin2, HIGH);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
    // if the state is '0' the DC motor will turn off
    if (state == '0') {
        digitalWrite(motorPin11, LOW); // set pin 2 on L293D low
        digitalWrite(motorPin21, LOW); // set pin 7 on L293D low
        digitalWrite(motorPin12, LOW); 
        digitalWrite(motorPin22, LOW); 
        if(flag == 0){
          Serial.println("Motor: av");
          flag=1;
        }
    }
    // if the state is '1' the motor will turn right
    else if (state == '1') {
        digitalWrite(motorPin11, LOW); // set pin 2 on L293D low
        digitalWrite(motorPin21, HIGH); // set pin 7 on L293D high
        digitalWrite(motorPin12, LOW); 
        digitalWrite(motorPin22, HIGH); 
        if(flag == 0){
          Serial.println("Motor: Forover");
          flag=1;
        }
    }
    // if the state is '2' the motor will turn left
    else if (state == '2') {
        digitalWrite(motorPin11, HIGH); // set pin 2 on L293D high
        digitalWrite(motorPin21, LOW); // set pin 7 on L293D low
        digitalWrite(motorPin12, HIGH);
        digitalWrite(motorPin22, LOW); 
        if(flag == 0){
          Serial.println("Motor: Bakover");
          flag=1;
        }
    }
}
/*
simple control test
*/
volatile int gear = 150; //default speed First Gear

volatile char val;         // variable to receive data from the serial port
byte M1L = 3;              // PWM left drive motor 
byte M2L = 5;              // PWM left drive motor
byte M1R = 9;              // PWM right drive motor
byte M2R = 6;              // PWM right drive motor
byte ledpin = 13;          // LED connected to pin 2 (on-board LED)

          /*IMPORTANT*/
//M1 => High & M2 => Low: forward movement
//M1 => Low & M2 => High: Backward movement

void setup()
{
  pinMode(ledpin, OUTPUT);  // pin 13 (on-board LED) as OUTPUT
  pinMode(M1L, OUTPUT);                                
  pinMode(M1R, OUTPUT);
  pinMode(M2L, OUTPUT);                                
  pinMode(M2R, OUTPUT);
  Serial.begin(9600);       // start serial communication at 115200bps
  Help();
}

void loop() {
  if( Serial.available() > 0)       // if data is available to read
  { 
    digitalWrite(ledpin, HIGH); // this will turn on the LED if you receive a command
    
    val = Serial.read();
    volatile int skewGear = gear/2;
    if(val == '1')
     {
      Serial.println("First Gear ");
      gear = 150;
     }
     if (val == '2')
     { 
       Serial.println("Second Gear ");
       gear = 200;
     }
    if (val == '3')
     { 
       Serial.println("Third Gear ");
       gear = 255;
     }
    
    
    if( val == 'W' || val == 'w' )//forwards               
    {
      Serial.println("Moving Forwards"); 
     //      Left Motor     :     Right Motor
      analogWrite(M1L, gear); analogWrite(M1R, gear);
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);                 
    }
    else if( val == 'S' || val == 's' )//backwards              
    {
      Serial.println("Moving Backwards");
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW);
      analogWrite(M2L, gear); analogWrite(M2R, gear);                   
    }
    else if( val == 'A' || val == 'a' )//Left         
    {
      Serial.println("LEFT");
      digitalWrite(M1L, LOW); analogWrite(M1R, gear);
      analogWrite(M2L, gear); digitalWrite(M2R, LOW);                      
    }
   else if( val == 'D' || val == 'd' )              
    {
      Serial.println("RIGHT");   
      analogWrite(M1L, gear);digitalWrite(M1R, LOW);
      digitalWrite(M2L, LOW); analogWrite(M2R, gear);                 
    }
    else if( val == 'T' || val == 't' )              
    {
      Serial.println("Skew Left Forward");   
      analogWrite(M1L, skewGear); analogWrite(M1R, gear);
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);                  
    }
    else if( val == 'Y' || val == 'y' )              
    {
      Serial.println("Skew Right Forward");  
      analogWrite(M1L, gear); analogWrite(M1R, skewGear); 
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);                  
    }
    else if( val == 'G' || val == 'g' )              
    {
      Serial.println("Skew Left Backward");   
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW);
      analogWrite(M2L, skewGear); analogWrite(M2R, gear);                  
    }
    else if( val == 'H' || val == 'h' )              
    {
      Serial.println("Skew Right Backward");   
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW);
      analogWrite(M2L, gear); analogWrite(M2R, skewGear);                  
    }
    else if(val == ' ' || val == 'x' || val == 'X')  // motors will stop if space bar is hit or x|X
    {
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW); 
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);
    }
    else if(val == '*') {
      Help();
    }
    else{}    
  }
  else{
    digitalWrite(ledpin, LOW);
  }
}

void Help() {
  Serial.println("Commands, Press * to bring up help menu");
  Serial.println("W = Forward");
  Serial.println("S = Backward");
  Serial.println("A = Left");
  Serial.println("D = Right");
  Serial.println("T = Skew Forward Left");
  Serial.println("Y = Skew Forward Right");
  Serial.println("G = Skew Backward Left");
  Serial.println("H = Skew Backward Right");
  Serial.println("Space Bar = All stop");
  return; 
}

