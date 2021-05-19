#include <SimpleDHT.h>
int pinDHT11 = 2;
SimpleDHT11 dht11;
#define debugSerial SerialUSB 
int sensorValue = 0;  
int outputValue = 0;  

void setup() { 
  pinMode(A0,INPUT);
  debugSerial.begin(57600);   
  while ((!debugSerial) && (millis() < 10000)) ;
  } 
  
  void loop() { 
    debugSerial.println("=================================");
    debugSerial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    debugSerial.print("Read DHT11 failed, err="); debugSerial.println(err);delay(1000);
    return;
  }
  
  debugSerial.print("Sample OK: ");
  debugSerial.print((int)temperature); debugSerial.print(" *C, "); 
  debugSerial.print((int)humidity); debugSerial.println(" H");
  sensorValue = analogRead(A0);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  debugSerial.print("Lumière = ");debugSerial.println(outputValue);
  // DHT11 sampling rate is 1HZ.
  delay(1500);
    }
