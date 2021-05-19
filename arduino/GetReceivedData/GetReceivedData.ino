#include <OrangeRn2483.h>

#define debugSerial SerialUSB

// The following keys are for structure purpose only. You must define YOUR OWN. 
const int8_t appEUI[8] = { 0x45, 0x78, 0x70, 0x4C, 0x6F, 0x52, 0x65, 0x72 };
const int8_t appKey[16] = { 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1E, 0xC8, 0xBE };
bool first = true;
  
bool joinNetwork()
{             
  debugSerial.print("devEUI = "); debugSerial.println(OrangeRN2483.getSysCmds()->getHardwareDevEUI());  
  OrangeRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz

  return OrangeRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  debugSerial.begin(57600); 
  
  while ((!debugSerial) && (millis() < 10000)) ;

  OrangeRN2483.init();
  debugSerial.println("Start");

  if(joinNetwork()){
    debugSerial.println("Join : success");
    OrangeRN2483.enableAdr();
  } else {
    debugSerial.println("Join : fail");
  }
}

bool SendLoRaMessage()
{
  const uint8_t size = 5;
  int8_t port = 5;
  int8_t data[size] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F };

  return OrangeRN2483.sendMessage(UNCONFIRMED_MESSAGE, data, size, port); 
}

// the loop function runs over and over again until power down or reset
void loop() {

  if(first)
  {
    //first = false;
    if(OrangeRN2483.getJoinState())
    {     
      if(SendLoRaMessage())
      {
        DownlinkMessage* downlinkMessage = OrangeRN2483.getDownlinkMessage();
        debugSerial.print("Port :");debugSerial.println(downlinkMessage->getPort());
        
        const String msgStr = downlinkMessage->getMessage();
        int8_t len = 0;
        const char* msgByte = (const char*)downlinkMessage->getMessageByteArray(&len);
        
        if(msgStr != NULL) debugSerial.print("Msg str :"); debugSerial.println(msgStr.c_str());
        
        if(msgByte != NULL){
          debugSerial.print("Msg array : ");
                    
          for(int i = 0; i < len; i++){
            debugSerial.print(msgByte[i], HEX);
          }
        }
                
      }
      
      delay(20000);

    }
    else debugSerial.println("Stop programm");
  }
}


