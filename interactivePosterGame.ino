// Slider 1
int motor1A = 2;
int motor1B = 4;
int motor1SpeedPin = 3;
int motor1poti = A0;
int motor1potivalue = 0;

// Slider 2
int motor2A = 8;
int motor2B = 7;
int motor2SpeedPin = 9;
int motor2poti = A1;
int motor2potivalue = 0;

// Slider 3
int motor3A = 12;
int motor3B = 13;
int motor3SpeedPin = 11;
int motor3poti = A2;
int motor3potivalue = 0;

// Sensor
int sensor = A3;
int sensorValue = 0;
boolean isInAction = false;

int counterFader1 = 0; // counter for movement
int maxcountFader1 = 7; // maximum movemtents

int counterFader2 = 0; // counter for movement
int maxcountFader2 = 7; // maximum movemtents

long randomNumber;

int match = 0;
boolean restart = false;

long previousMillis = 0;

long interval = 5000;
long intervalRestart = 8000;

void setup() {
  // init all that stuff
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  
  calibrateFader();
  
  }

void loop() {
  
  unsigned long currentMillis = millis();
  
  sensorValue = analogRead(sensor);
  Serial.println(isInAction);
  

  if(isInAction == false) {
    sensorValue = analogRead(sensor);
  }
  
  if(motor3potivalue > 920) {
    if((currentMillis - previousMillis > intervalRestart)) {
      if(currentMillis - previousMillis > interval) {
        if(sensorValue > 300) {
          isInAction = true;
        }
      }
    }
  }

  motor1potivalue =  analogRead(motor1poti); // read the poti
  motor2potivalue =  analogRead(motor2poti); // read the poti
  motor3potivalue =  analogRead(motor3poti); // read the poti
  

  // if the counter is smaller than the maxcounter
  // we keep on moving the fader
  // if it excedess there is no movement
  if(isInAction == true) {
    movetheFader();
    previousMillis = currentMillis;
  }
  
  faderMatchMove();
  
  if(currentMillis - previousMillis > interval) {
    faderRestart();
  }
  
}

/***
  * This function moves the fader and
  * increases the counter
  *
  */
void movetheFader() {
  
  // FADER 1
  if (counterFader1 < maxcountFader1) {
  
    // Slider 1 Direction one
    if (motor1potivalue > 750) {
      digitalWrite(motor1A, HIGH);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor1B, LOW);   // motor direction two pin switched to LOW  (GND)
      analogWrite(motor1SpeedPin, 160);  // and write it as speed to the speed pin
      if(counterFader1 % 2 == 0){
        counterFader1++;
      }
    }
        
    // Slider 1 Direction two
    if (motor1potivalue < 250) {
      digitalWrite(motor1A, LOW);   // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor1B, HIGH);  // motor direction two pin switched to LOW  (GND)
      analogWrite(motor1SpeedPin, 160);  // and write it as speed to the speed pin
      if(counterFader1 % 2 == 1){
        counterFader1++;
      }
    }
  }
   
  else {
    // Slider 1 Stop
    analogWrite(motor1SpeedPin, 0);  // and write it as speed to the speed pin
    digitalWrite(motor1A, LOW); // motor direction one pin switched to HIGH (+5V)
    digitalWrite(motor1B, LOW); // motor direction two pin switched to LOW  (GND)
  }
  
  //  FADER 2
  if (counterFader2 < maxcountFader2) {
    
    // Slider 2 Direction one
    if (motor2potivalue > 750) {
      digitalWrite(motor2A, HIGH);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor2B, LOW);   // motor direction two pin switched to LOW  (GND)
      analogWrite(motor2SpeedPin, 180);  // and write it as speed to the speed pin
      if(counterFader2 % 2 == 0){
        counterFader2++;
      }
    } 
      
    // Slider 2 Direction two
    if (motor2potivalue < 250) {
      digitalWrite(motor2A, LOW);   // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor2B, HIGH);  // motor direction two pin switched to LOW  (GND)
      analogWrite(motor2SpeedPin, 180);  // and write it as speed to the speed pin
      if(counterFader2 % 2 == 1){
        counterFader2++;
      }
    }
  }
  
  else {
    // Slider 2 Stop
    analogWrite(motor2SpeedPin, 0);  // and write it as speed to the speed pin
    digitalWrite(motor2A, LOW); // motor direction one pin switched to HIGH (+5V)
    digitalWrite(motor2B, LOW); // motor direction two pin switched to LOW  (GND)
      
    if(counterFader1 == maxcountFader1) {
      // Slider 1 Stop
      analogWrite(motor1SpeedPin, 0);  // and write it as speed to the speed pin
      digitalWrite(motor1A, LOW); // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor1B, LOW); // motor direction two pin switched to LOW  (GND)
      
      if(randomNumber == 1){
        match = 1; 
      } 
  
      else {
        match = 2; 
      }
      
      isInAction = false;
      
      // Random counter
      randomNumber = random(2);
      maxcountFader2 = 7;
      maxcountFader2 = maxcountFader2 + randomNumber;

      counterFader1 = 0;
      counterFader2 = 0;
    }
  }
}

void faderMatchMove() {
  if(match == 1){
    if (motor3potivalue > 920) {
      digitalWrite(motor3A, HIGH);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor3B, LOW);  // motor direction one pin switched to HIGH (+5V)
      analogWrite(motor3SpeedPin, 200);  // and write it as speed to the speed pin
    }
    
    if (motor3potivalue < 110) {
      digitalWrite(motor3A, LOW);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor3B, LOW);  // motor direction one pin switched to HIGH (+5V)
      analogWrite(motor3SpeedPin, 0);  // and write it as speed to the speed pin
      restart = true;
    }
  }
  
  if(match == 2){
    if (motor3potivalue > 920) {
      digitalWrite(motor3A, HIGH);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor3B, LOW);  // motor direction one pin switched to HIGH (+5V)
      analogWrite(motor3SpeedPin, 200);  // and write it as speed to the speed pin
    }
    
    if (motor3potivalue < 530) {
      digitalWrite(motor3A, LOW);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor3B, LOW);  // motor direction one pin switched to HIGH (+5V)
      analogWrite(motor3SpeedPin, 0);  // and write it as speed to the speed pin
      restart = true;
    }
  }
}

void faderRestart() {
    if (restart == true) {
      digitalWrite(motor3A, LOW);  // motor direction one pin switched to HIGH (+5V)
      digitalWrite(motor3B, HIGH);  // motor direction one pin switched to HIGH (+5V)
      analogWrite(motor3SpeedPin, 200);  // and write it as speed to the speed pin
     
      if (motor3potivalue > 920) {
        digitalWrite(motor3A, LOW);  // motor direction one pin switched to HIGH (+5V)
        digitalWrite(motor3B, LOW);  // motor direction one pin switched to HIGH (+5V)
        analogWrite(motor3SpeedPin, 0);  // and write it as speed to the speed pin
        match = 0;
        restart = false;
      }
    }
}

//Calibrates the min and max position of the fader
void calibrateFader() {
  //Send fader to the top and read max position
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, HIGH);
  //digitalWrite(motor3A, HIGH);
  delay(400);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  //digitalWrite(motor3A, LOW); 
    
  //Send fader to the bottom and read max position
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2B, HIGH);
  //digitalWrite(motor3B, HIGH);
  delay(400);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2B, LOW);
  //digitalWrite(motor3B, LOW);
}
