#include "Ubidots.h"


const char* UBIDOTS_TOKEN = "";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() 
{
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  //ubidots.setDebug(true); 
}

void loop() 
{
  int value1 = random(0, 100);
  int value2 = random(100, 300);
  
  ubidots.add("Random_num_1", value1);  
  ubidots.add("Random_num_2", value2);

  bool bufferSent = false;
  bufferSent = ubidots.send();  

  if (bufferSent) 
  {
   Serial.println("Values sent by the device");
  }

  delay(5000);
}
