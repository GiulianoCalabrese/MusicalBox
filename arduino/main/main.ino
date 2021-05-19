#include <OrangeRn2483.h>
#include <LpwaOrangeEncoder.h>
#include <SimpleDHT.h>
int pinDHT11 = 2;
int anemometre = 3;
SimpleDHT11 dht11;
//#define debugSerial SerialUSB
int sensorValue = 0;  
int outputValue = 0;  
int gaslevel = 0;
int gasvalue = 0;
unsigned long vent = 0;
// The following keys are for structure purpose only. You must define YOUR OWN. 
const int8_t appEUI[8] = { 0x45, 0x78, 0x70, 0x4C, 0x6F, 0x52, 0x65, 0x72 };
const int8_t appKey[16] = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1E, 0xC8, 0xBE };

bool joinNetwork()
{             
  OrangeRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz
  return OrangeRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  pinMode(A0,INPUT);
  pinMode(A1, INPUT);
  pinMode(anemometre, INPUT); 
  //debugSerial.begin(57600); 
  //while ((!debugSerial) && (millis() < 10000)) ;
  OrangeRN2483.init();
}

bool SendLoRaMessage(int input1,int input2,int input3, int input4, int input5)
{
  int8_t size = 1;
  int8_t port = 5;
  //int32_t final = (input1 & 0x000000FF) | (( input2 & 0x000000FF ) << 8) | (( input3 & 0x000000FF ) << 16) | (( input4 & 0x000000FF ) << 24);// | (( input5 & 0x000000FF ) << 32);
  LpwaOrangeEncoder.flush();
  String input;
  input.concat(input1);input.concat(input2);input.concat(input3);input.concat(input4);input.concat(input5);
  //debugSerial.println(input.toInt());
  //debugSerial.println(final);
  LpwaOrangeEncoder.addInt(input.toInt());///LpwaOrangeEncoder.addInt(input2);LpwaOrangeEncoder.addInt(input3);LpwaOrangeEncoder.addFloat(input4);
  int8_t* frame = LpwaOrangeEncoder.getFramePayload(&size);
  return OrangeRN2483.sendMessage(frame , size, port); // send unconfirmed message
}

void loop() {
  delay(10000);
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //debugSerial.print("Read DHT11 failed, err="); debugSerial.println(err);
    return;
  }
    bool res = joinNetwork();
    if(res)
    {
      //debugSerial.println("Join Success");
      OrangeRN2483.enableAdr();
      sensorValue = analogRead(A0);
      outputValue = map(sensorValue, 0, 1023, 0, 10);
      gaslevel = analogRead(A1);
      gasvalue = map(gaslevel, 0, 1023, 0, 99);
      vent = Comptage(anemometre,HIGH,1000000);
      //debugSerial.println((int)temperature);debugSerial.println((int)humidity);debugSerial.println(outputValue);debugSerial.println(gasvalue);debugSerial.println(vent);
      SendLoRaMessage((int)temperature,(int)humidity,outputValue,gasvalue,vent);  
    }else //debugSerial.println("Join Failed");
    delay(3600000);
}

long count = 0;
unsigned long Comptage(uint8_t pin, uint8_t state, unsigned long timeout)
{
  count =0;
  unsigned long startMicros = micros();

  while (micros() -  startMicros < timeout)
  {
  // wait for any previous pulse to end
  while (digitalRead(pin)  == state) {
      if (micros() - startMicros > timeout)
        return count;
  }
  count++;
   
  // wait for the pulse to start
  while ((digitalRead(pin)) != state) {
    if (micros() - startMicros > timeout)
       return count;
       }
  }
  return count;
}

