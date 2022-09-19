#include "Ubidots.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

const char* UBIDOTS_TOKEN = "";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() 
{
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  //ubidots.setDebug(true); 
  dht.begin();
}

void loop() 
{
  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  ubidots.add("Temperature", t);  
  ubidots.add("Humidity", h);

  bool bufferSent = false;
  bufferSent = ubidots.send();  

  if (bufferSent) 
  {
   Serial.println("Values sent by the device");
  }

  delay(5000);
}
