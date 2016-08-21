
//                 +-\/-+
// ADC0 (D 5) PB5 1|    |8 Vcc
// ADC3 (D 3) PB3 2|    |7 PB2 (D 2) ADC1
// ADC2 (D 4) PB4 3|    |6 PB1 (D 1) PWM1
//            GND 4|    |5 PB0 (D 0) PWM0
//                 +----+

int sensorPin = 3;    // select the input pin for the potentiometer
int led1 = PB0;
int led2 = PB1;
int led3 = PB2;
int led4 = PB3;

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

