#include "WiFi.h"

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
  // put your main code here, to run repeatedly:

}
