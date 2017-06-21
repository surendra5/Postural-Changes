int inputPin = A0;

int average = 0;

int ledState = LOW; 

int sensorValue = analogRead(inputPin);

const int ledPin =  LED_BUILTIN;

// will store last time LED was updated
unsigned long previousMillis = 0;

// interval at which to blink (milliseconds)
const long interval = 1000;

void setup() {
  int sensorValue = analogRead(inputPin);
  
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
     
  for (int i=0; i < 10; i++) {
      average = average + sensorValue;
      delay(100);
    }
  
  average = average/10;
  //convert analogInputValue to voltage, 
  //float average = average * (5.0 / 1023.0);
   
}

void loop() {

        int sensorValue = analogRead(inputPin);
        
        // to convert into voltage
        //float sensorValue  = sensorValue * (5.0 / 1023.0);
        
        // main loop:
        if ( sensorValue > average){
            digitalWrite(ledPin, HIGH);
          }
        else if( sensorValue < average){
            digitalWrite(ledPin, LOW);
          }
        else {
              //to blink without delay
              //to drive motor continously in on-off state, on-off vibrations
              unsigned long currentMillis = millis();
              
              if (currentMillis - previousMillis >= interval) {
                  // save the last time you blinked the LED
                  previousMillis = currentMillis;
              
                  // if the LED is off turn it on and vice-versa:
                  if (ledState == LOW) {
                    ledState = HIGH;   
                  } 
                  else {
                    ledState = LOW;                   
                  }              
                  // set the LED with the ledState of the variable:
                  digitalWrite(ledPin, ledState);
               }
           }
        Serial.println(average);
        Serial.println(analogRead(inputPin));
  }

