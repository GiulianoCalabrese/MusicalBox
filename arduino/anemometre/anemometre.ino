#define debugSerial SerialUSB
int anemometre = 3;
void setup()
{
  pinMode(anemometre, INPUT);      
  debugSerial.begin(57600); 
  while ((!debugSerial) && (millis() < 10000)) ;                            
}
unsigned long vent = 0;
void loop()
{
    vent = pulseInLong(anemometre,HIGH,10000000);
    debugSerial.println(vent);
    float valeur = 0;
    if (vent >0){
      valeur = (70000.0*6.2/vent)*3.6;
    }
    //debugSerial.println(valeur);*/
    delay(5000);
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
  unsigned long startMicros = micros();
  /*  if (digitalRead(pin) == state)
       debugSerial.print("HAUT");
    else
       debugSerial.print("BAS");*/
       
  // wait for any previous pulse to end
  while (digitalRead(pin)  == state) {
   // debugSerial.println("1A");
    if (micros() - startMicros > timeout){
    //debugSerial.println("timeout_1B");
      return 0;
    }
  }

  // wait for the pulse to start
  while ((digitalRead(pin)) != state) {
    //debugSerial.println("2A");
    if (micros() - startMicros > timeout){
    //debugSerial.println("timeout_2B");
      return 0;}
  }

  unsigned long start = micros();
  // wait for the pulse to stop
  while (digitalRead(pin) == state) {
    //debugSerial.println("3A");
    if (micros() - startMicros > timeout){
    //debugSerial.println("timeout_3B");
      return 0;
    }
  }
  return micros() - start;
}
