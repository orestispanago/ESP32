#include "WiFi.h"
#include "ESP32Ping.h"
#include "config.h"

const char* ssid = WIFI_SSID;
const char* password =  WIFI_PASSWORD;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  bool success = Ping.ping("www.google.com", 3);
 
  if(!success){
    Serial.println("Ping failed");
    return;
  }
 
  Serial.println("Ping succesful.");
  delay(5000);
}
