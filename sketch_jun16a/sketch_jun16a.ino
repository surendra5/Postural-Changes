/* for vibration motor of max_volatge = 3.0 using pwm value 170 max only in case of not using any resistance for voltage drop */


const int inputPin = A4;

int average = 0;

int averageL = 0;

int averageH = 0;

int doubleAverage = 0;
int oneHalfAverage = 0;

int ledState = 0; 

const int outPutPin =  6;

// will store last time vibrator was updated
unsigned long previousMillis = 0;

unsigned long previousA = 0;

unsigned long previousOHA = 0;

unsigned long previousDA = 0;

// interval at which to blink (milliseconds)
const long interval = 1000;

const long intervalA = 300000;

const long intervalOHA = 300000;

const long intervalDA = 300000;

void setup() {
  float sensorValue = analogRead(inputPin);
  
  // put your setup code here, to run once:
  pinMode(outPutPin, OUTPUT);
  
  Serial.begin(9600);
     
  for (int i=0; i < 10; i++) {
      average = average + sensorValue;
      //vibrate for one sec after taking each value while auto-calibrating at medium intensity
     // analogWrite(outPutPin, 100);
      delay(1000);
    }
  // when auto-calibration completes vibrate for 5 sec at full intensity
  //analogWrite(outPutPin, 140);
  //delay(5000);

  //calculate average and other values for different pysiological conditions
  average = average/10;
  average = average + 400;
//  averageH = average * 1.25;
  averageL = average * 0.5;
  oneHalfAverage = average * 1.5; 
  doubleAverage = average * 2;
  Serial.println(average);
  //convert analogInputValue to voltage, 
  //float average = average * (5.0 / 1023.0);
   
}

void loop() {

        // taking input from flex sensor
       int sensorValue = analogRead(inputPin);
        Serial.println(analogRead(inputPin));
        // to convert into voltage
        //float sensorValue  = sensorValue * (5.0 / 1023.0);
        
        // main loop:
 /* int a = 21;
  if (a == 20 ){
  //  unsigned long currentMillihs = millis();
    Serial.println("dsds");
  }*/
       // critical case, hard-alert patient
        if( sensorValue > doubleAverage ){
            unsigned long currentDA = millis();
            if ( currentDA - previousDA >= intervalDA){                
                previousDA = currentDA;                
                Serial.println("ab");
                analogWrite(outPutPin, 170);
            }
        }

        // medium alert, warn patient for critical case
        else if ( sensorValue > oneHalfAverage){
          
            unsigned long currentOHA = millis();            
            if ( currentOHA - previousOHA >= intervalOHA){
                previousOHA = currentOHA; 
                Serial.println("ac");               
                analogWrite(outPutPin, 140);            
            }            
        }
/*
        // primary alert, alert patient
        else if ( sensorValue < average){
            unsigned long currentA = millis();
            if ( currentA - previousA >= intervalA){
                previousA = currentA;    
                Serial.println("ad");         
                analogWrite(outPutPin, 110);    
            }    
        }
        */
        // normal case, good posture
        // TO-DO, may set interval in place of average
        else if( sensorValue > averageL && sensorValue < oneHalfAverage){
          Serial.println("af");
          Serial.println(averageL);
          Serial.println(oneHalfAverage);
          
            analogWrite(outPutPin, 170);
             }
             
     /*   -ve value, koi hootiya agr jyada peeche mudne me mahir ho toh
      *    some value less than average
      *    else if( sensorValue < average){
            analogWrite(outPutPin, 0);
             }

      */
        else   { 
              // equal condition
              // if there is no input, i.e., sensorValue is zero
              //if average and  sensorVakue both are zero 
              
              //to blink without delay
              //to drive motor continously in on-off state, on-off vibrations
                unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == 0) {
      ledState = 170;
    } else {
      ledState = 0;
    }

    // set the LED with the ledState of the variable:
    analogWrite(outPutPin, ledState);
    Serial.println("aa");
                  /*Serial.println(average);
                 
              */}
         }
          
       
  }

