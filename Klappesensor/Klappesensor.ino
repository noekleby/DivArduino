const int buttonPin = 2; 
const int ledPin = 0; 

int buttonstate = 0;
int ledstate = 0;

void setup() {

  pinMode(ledPin, OUTPUT); 

  pinMode(buttonPin, INPUT); 
}

void loop(){

  buttonstate = digitalRead(buttonPin);
  ledstate = digitalRead(ledPin);

  if (ledstate == HIGH && buttonstate == LOW) { 
    delay(250);
    digitalWrite(ledPin, LOW); 
  }
  if (ledstate == LOW && buttonstate == LOW) { 
    delay(250);
    digitalWrite(ledPin, HIGH); 
  }
}
