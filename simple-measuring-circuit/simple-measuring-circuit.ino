// Gas Sensor Variables
int gasSensor = A0;
int gasVal = 0;
int badVal = 10;
int interval = 1000;

// Flipdot Variables
int flip = 11;
int flop = 10;

// Initialize Motor
#define DIR_PIN 2
#define STEP_PIN 3

void setup() {
  Serial.begin(9600);

  pinMode(flip,OUTPUT);
  pinMode(flop,OUTPUT);

  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT); 

  dotBlack();
}

void loop() {
  gasVal = analogRead(gasSensor);
  Serial.println(gasVal);

  if (gasVal >= badVal) {
    dotRed();
    
    rotate(1000, .5); 
    delay(10); 
    rotate(0, .25); //reverse
    delay(10); 
  }
  else {
    dotBlack(); 
  }

  // Check every second
  delay(interval);
}

void dotRed() {
  digitalWrite(flip,HIGH);
  digitalWrite(flop,LOW);
  delay(20);
  digitalWrite(flip,LOW);

}
void dotBlack() {
  digitalWrite(flip,LOW);
  digitalWrite(flop,HIGH); 
  delay(20);
  digitalWrite(flop,LOW);
}
void rotate(int steps, float speed){ 
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN,dir); 

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  }  
}


