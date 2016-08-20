
int sensorPin = 12;    // select the input pin for the potentiometer
int led1 = 0;
int led2 = 1;
int led3 = 2;
int led4 = 3;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  int v = 0;
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  
  v = analogRead(sensorPin);
  if (v < 400){
    digitalWrite(led1,HIGH); 
  }
  if (v < 370){
    digitalWrite(led2,HIGH);
  }
  if (v < 330){
    digitalWrite(led3,HIGH);
  }
  if (v < 230){
    digitalWrite(led4,HIGH);
  }
}

