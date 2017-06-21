int input = A0;
int average = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
   
   for (int i=0; i < 10; i++) {
        average = average + analogRead(input);
   delay(100);
   }
   average = average/10;
   //average = 5 * average/1024
   
}

void loop() {
  // put your main code here, to run repeatedly:
  if (analogRead(input) > average){
      digitalWrite(LED_BUILTIN, HIGH);
    }
  else if( analogRead(input) < average){
      digitalWrite(LED_BUILTIN, LOW);
    }
  else {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
    Serial.println(average);
   Serial.println(analogRead(input));  
}
