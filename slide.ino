//constants
const int topSensor = A1;
const int bottomSensor = A0;
const int redLight = 10;
const int greenLight = 11;
const int yellowLight = 12;
const int resetButton = 13;
const int initialBrightLight = 900;
const int passingLight = 100;
const unsigned long waitingTime = 5000; //5sec

bool begin = false;
int counter = 0;
bool topPassingStarted = false;
bool topPassed = false;
bool bottomPassingStarted = false;
bool bottomPassed = false;
bool error = false;

unsigned long timeTopPassed;

void setup() {
  Serial.begin(9600);
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(yellowLight, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);
}

void loop() {
  int valueB = analogRead(bottomSensor);
  int valueT = analogRead(topSensor);
  
  //waiting until both sensors have enough light to initialize the system
  if(!begin && valueT >= initialBrightLight && valueB >= initialBrightLight) {
    begin = true;
    digitalWrite(greenLight, HIGH);
    digitalWrite(redLight, LOW);
    digitalWrite(yellowLight, LOW);

  }
  
  if(begin && !error) {
    if(valueT <= passingLight) {
      topPassingStarted = true;
    } else if(topPassingStarted) {
      topPassingStarted = false;
      topPassed = true;
      digitalWrite(greenLight, LOW);
      digitalWrite(redLight, HIGH);
      timeTopPassed = millis();
    }
    
    if(topPassingStarted && topPassed) {
      error = true;
    }
    
    if(topPassed && millis() - timeTopPassed >= waitingTime) {
      error = true;
    }
    
    if(valueB <= passingLight) {
      bottomPassingStarted = true;
    } else if(bottomPassingStarted) {
      if(topPassed) {
        topPassed = false;
        digitalWrite(greenLight, HIGH);
        digitalWrite(redLight, LOW);
      }
      bottomPassingStarted = false;
      bottomPassed = true;
    }
    
    if(bottomPassingStarted && bottomPassed) {
      error = true;
    }
    
    if(!topPassed && bottomPassingStarted) {
      error = true;
    }
    
    if(topPassingStarted && bottomPassingStarted) {
      error = true;
    }
  }
  
  if(error) {
  	digitalWrite(greenLight, LOW);
    digitalWrite(redLight, HIGH);
    digitalWrite(yellowLight, HIGH);
  }
  
  if(digitalRead(resetButton) == LOW){
    topPassed = false;
    topPassingStarted = false;
    bottomPassed = false;
    bottomPassingStarted = false;
    begin = false;
    error = false;
  }
}
