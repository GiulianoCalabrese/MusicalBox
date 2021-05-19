#include <OrangeRn2483.h>

#define debugSerial SerialUSB

#define DHTPIN A8     // what pin we're connected to

// The following keys are for structure purpose only. You must define YOUR OWN. 
const int8_t appEUI[8] = { 0x45, 0x78, 0x70, 0x4C, 0x6F, 0x52, 0x65, 0x72 };
const int8_t appKey[16] = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1E, 0xC8, 0xBE };

bool first = true;
  
bool joinNetwork()
{             
  OrangeRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz
  return OrangeRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  pinMode(8, INPUT);
  debugSerial.begin(57600); 
  
  while ((!debugSerial) && (millis() < 10000)) ;

  OrangeRN2483.init();
}

bool SendLoRaMessage()
{
  const uint8_t size = 5;
  int8_t port = 5;
  int8_t data[size] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // Hello

  return OrangeRN2483.sendMessage(data, size, port); // send unconfirmed message
}

void loop() {
  int buttonState = digitalRead(8);
  debugSerial.println(buttonState); 
  delay(5000);
  if(first)
  {
    //first = false;
    debugSerial.println("Join Request");
    bool res = joinNetwork();
    if(res)
    {
      debugSerial.println("Join Success");
      OrangeRN2483.enableAdr();

      debugSerial.println("Send Message #1");
      SendLoRaMessage();
      delay(20000);
      debugSerial.println("Send Message #2");
      SendLoRaMessage();
      delay(20000);
      debugSerial.println("Send Message #3");
      SendLoRaMessage();      
    }else debugSerial.println("Join Failed");
    debugSerial.println("Program Finished");
  }
}



