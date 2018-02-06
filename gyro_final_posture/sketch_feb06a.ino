#include<Wire.h>

const int MPU_addr = 0x68;

int16_t axis_X, axis_Y, axis_Z;

const int outPutPin = 6;

int minVal = 265;

int maxVal = 402;


double x;

double y;

double z;
//thresold variables
double avgGyro, avgGyroVH, avgGyroH, avgGyroL, avgGyroVL;

double total = 0;

int i;

// will store last time vibrator was updated
unsigned long previousMillis = 0;

unsigned long previousMillisG = 0;

unsigned long previousL = 0;

unsigned long previousVL = 0;

unsigned long previousVH = 0;

unsigned long previousH = 0;
//time delay in vibration
// interval at which to blink (milliseconds)
const long interval = 10000; //1000;

const long intervalA = 10000;//300000;

const long intervalOHA = 10000;//300000;

const long intervalDA = 10000;//300000;

void setup() {

  Wire.begin();

  Wire.beginTransmission(MPU_addr);

  Wire.write(0x6B);

  Wire.write(0);

  Wire.endTransmission(true);

  Serial.begin(9600);

  for (i = 0; i < 20 ; i++) {

    Wire.beginTransmission(MPU_addr);

    Wire.write(0x3B);

    Wire.endTransmission(false);

    Wire.requestFrom(MPU_addr, 14, true);

    axis_X = Wire.read() << 8 | Wire.read();

    axis_Y = Wire.read() << 8 | Wire.read();

    axis_Z = Wire.read() << 8 | Wire.read();

    int xAng = map(axis_X, minVal, maxVal, -90, 90);

    int yAng = map(axis_Y, minVal, maxVal, -90, 90);

    int zAng = map(axis_Z, minVal, maxVal, -90, 90);


    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);

    //   y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);

    //   z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    total = total + x;
    avgGyro = total / 20;
    Serial.println("avgGyro");
    Serial.println(avgGyro);
    avgGyroVH = avgGyro + 4;
    avgGyroH = avgGyro + 2.5;
    avgGyroL = avgGyro - 2.5;
    avgGyroVL = avgGyro - 4;
  }


}

void loop() {

  Wire.beginTransmission(MPU_addr);

  Wire.write(0x3B);

  Wire.endTransmission(false);

  Wire.requestFrom(MPU_addr, 14, true);

  axis_X = Wire.read() << 8 | Wire.read();

  axis_Y = Wire.read() << 8 | Wire.read();

  axis_Z = Wire.read() << 8 | Wire.read();

  int xAng = map(axis_X, minVal, maxVal, -90, 90);

  int yAng = map(axis_Y, minVal, maxVal, -90, 90);

  int zAng = map(axis_Z, minVal, maxVal, -90, 90);


  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);

  //  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);

  //  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  static int flag_time = 0;

  Serial.print("Angle of inclination in X axis = ");

  Serial.print(x);

  Serial.println((char)176);

  if ( x > avgGyroVH ) {
    Serial.println("da");
    if (flag_time == 0) {
      unsigned long currentVH = millis();
      if ((unsigned long)(currentVH - previousVH) >= interval) {
        previousVH = currentVH;
        Serial.println("wrong posture - doubleAverage");
        analogWrite(outPutPin, 170);
      }
    }
    else {
      Serial.println("wrong posture - doubleAverage");
      analogWrite(outPutPin, 170);
      flag_time = 1;
    }
  }
  else if ( x > avgGyroH ) {
    Serial.println("a");
    //if returning form correct posture , then give time delay, otherwise not
    if (flag_time == 0) {
      unsigned long currentH = millis();
      if ((unsigned long)(currentH - previousH) >= interval) {
        previousH = currentH;
        Serial.println("wrong  - Average");
        //time delay for blink, bad pratice but simpler
        int j = 0; int i = 10000;
        for (j = 0; j < i; j++) analogWrite(outPutPin, 0);
        analogWrite(outPutPin, 170);
      }
    }
    else {
      Serial.println("wrong  - Average");
      int j = 0; int i = 10000;
      for (j = 0; j < i; j++) analogWrite(outPutPin, 0);
      analogWrite(outPutPin, 170);
      flag_time = 1;
    }
  }
  else if ( x < avgGyroH && x > avgGyroL ) {
    //if ( currentH - previousH >= intervalOHA){
    if (flag_time == 1) flag_time = 0;
    Serial.println("sahi");
    analogWrite(outPutPin, 0);
    //analogWrite(outPutPin, 170);
  }
  else if ( x < avgGyroL ) {
    if (flag_time == 0) {
      unsigned long currentL = millis();
      if ( (unsigned long)(currentL - previousL) >= interval) {
        previousL = currentL;
        analogWrite(outPutPin, 0);
        Serial.println("wrong  - LowAverage");
        analogWrite(outPutPin, 170);
      }
    }
    else {
      analogWrite(outPutPin, 0);
      Serial.println("wrong  - LowAverage");
      analogWrite(outPutPin, 170);
    }
  }
  else if ( x < avgGyroVL ) {
       if (flag_time == 0) {
      unsigned long currentVL = millis();
      if ((unsigned long)(currentVL - previousVL) >= interval) {
        previousVL = currentVL;
        analogWrite(outPutPin, 0);
        Serial.println("wrong - doubleLowAverage");
        analogWrite(outPutPin, 170);
      }
    }
    else {
      analogWrite(outPutPin, 0);
      Serial.println("wrong - doubleLowAverage");
      analogWrite(outPutPin, 170);
    }
  }
  //TO CHECK,
  else {
    unsigned long currentMillisG = millis();
    if ((unsigned long)(currentMillisG - previousMillisG) >= interval) {
      // save the last time you blinked the LED
      previousMillisG = currentMillisG;
    }
    Serial.println("check error");
    analogWrite(outPutPin, 0);
    analogWrite(outPutPin, 170);
  }
  /*  Serial.print("Angle of inclination in Y axis= ");
    Serial.print(y);
    Serial.println((char)176);
    Serial.print("Angle of inclination in Z axis= ");
    Serial.print(z);
    Serial.println((char)176);*/

  //Serial.println("-------------------------------------------");
  //not to use delay
  delay(1000);

}
