#define debugSerial SerialUSB
int gaslevel = 0;
void setup()
{
  pinMode(A0, INPUT);      
  debugSerial.begin(57600); 
  while ((!debugSerial) && (millis() < 10000)) ;                            
}
 
void loop()
{
    gaslevel = analogRead(A0);
    debugSerial.println(gaslevel);
}


