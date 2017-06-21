int analogPin=9;
int i=0;
 
void setup()
{
Serial.begin(9600);
}
 
void loop()
{
  for(i=0;i<170;i++)
  {
   analogWrite(analogPin, i); 
   Serial.println(i);
   delay(50);
  }
  
  for( ; i>0;i--)
  {
   analogWrite(analogPin, i);
    Serial.println(i); 
   delay(50);
  }
  
 
}
