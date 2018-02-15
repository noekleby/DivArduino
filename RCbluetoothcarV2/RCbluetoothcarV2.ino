/*
RC-bilkontroller med alle retninger + giring
*/
volatile int gear = 150; //default speed forstegir

volatile char val;         // variable to receive data from the serial port
byte M1L = 3;              // PWM left drive motor 
byte M2L = 5;              // PWM left drive motor
byte M1R = 9;              // PWM right drive motor
byte M2R = 10;              // PWM right drive motor

//M1 => High & M2 => Low: forward movement
//M1 => Low & M2 => High: Backward movement

void setup()
{
  pinMode(M1L, OUTPUT);                                
  pinMode(M1R, OUTPUT);
  pinMode(M2L, OUTPUT);                                
  pinMode(M2R, OUTPUT);
  Serial.begin(9600);       // start serial communication at 115200bps
  Help();
  Serial.println("Press * for hjelp med kommandoer.");
}

void loop() {
  if( Serial.available() > 0)       // if data is available to read
  {     
    val = Serial.read();
    volatile int skewGear = gear/2;
    if(val == '1')
     {
      Serial.println("Forstegir ");
      gear = 150;
     }
     if (val == '2')
     { 
       Serial.println("Andregir ");
       gear = 200;
     }
    if (val == '3')
     { 
       Serial.println("Tredjegir ");
       gear = 255;
     }
    
    
    if( val == 'R' || val == 'r' )//forwards               
    {
      Serial.println("Forover"); 
     //      Left Motor     :     Right Motor
      analogWrite(M1L, gear); analogWrite(M1R, gear);
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);                 
    }
    else if( val == 'X' || val == 'x' )//backwards              
    {
      Serial.println("Bakover");
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW);
      analogWrite(M2L, gear); analogWrite(M2R, gear);                   
    }
    else if( val == 'D' || val == 'd' )//Left         
    {
      Serial.println("Venstre");
      digitalWrite(M1L, LOW); analogWrite(M1R, gear);
      analogWrite(M2L, gear); digitalWrite(M2R, LOW);                      
    }
   else if( val == 'G' || val == 'g' )              
    {
      Serial.println("Hoyre");   
      analogWrite(M1L, gear);digitalWrite(M1R, LOW);
      digitalWrite(M2L, LOW); analogWrite(M2R, gear);                 
    }
    else if( val == 'E' || val == 'e' )              
    {
      Serial.println("Skraa venstre forover");   
      analogWrite(M1L, skewGear); analogWrite(M1R, gear);
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);                  
    }
    else if( val == 'T' || val == 't' )              
    {
      Serial.println("Skraa hoyre forover");  
      analogWrite(M1L, gear); analogWrite(M1R, skewGear); 
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);                  
    }
    else if( val == 'Z' || val == 'z' )              
    {
      Serial.println("Skraa venstre bakover");   
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW);
      analogWrite(M2L, skewGear); analogWrite(M2R, gear);                  
    }
    else if( val == 'C' || val == 'c' )              
    {
      Serial.println("Skraa hoyre bakover");   
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW);
      analogWrite(M2L, gear); analogWrite(M2R, skewGear);                  
    }
    else if(val == ' ' || val == '0')  // motors will stop if space bar is hit or 0
    {
      digitalWrite(M1L, LOW); digitalWrite(M1R, LOW); 
      digitalWrite(M2L, LOW); digitalWrite(M2R, LOW);
    }
    else if(val == '*') {
      Help();
    }
    else{}    
  }
}

void Help() {
  Serial.println(" ");
  Serial.println("Kommandoer, press * for kommandohjelp");
  Serial.println("R = Forover");
  Serial.println("X = Bakover");
  Serial.println("D = Venstre");
  Serial.println("G = Hoyre");
  Serial.println("E = Skraa venstre forover");
  Serial.println("T = Skraa hoyre forover");
  Serial.println("Z = Skraa venstre bakover");
  Serial.println("C = Skraa hoyre bakover");
  Serial.println("Space eller 0 = Stopp");
  Serial.println("---------- Gir -----------");
  Serial.println("1 = Forstegir");
  Serial.println("2 = Andregir");
  Serial.println("3 = Tredjegir");
  return; 
}
