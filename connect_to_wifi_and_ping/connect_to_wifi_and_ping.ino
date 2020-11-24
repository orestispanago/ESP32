#include "WiFi.h"
#include "ESP32Ping.h"
#define ONBOARD_LED  2

const char* ssid = WIFI_SSID;
const char* password =  WIFI_PASSWORD;


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(ONBOARD_LED,OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void blink_function(){
    for (int i = 0; i <= 3; i++) {
    digitalWrite(ONBOARD_LED,HIGH);
    delay(50);
    digitalWrite(ONBOARD_LED,LOW);
    delay(150);
  }
}

void loop() {
  bool success = Ping.ping("www.google.com", 3);
 
  if(!success){
    Serial.println("Ping failed");
    return;
  }

  Serial.println("Ping succesful.");
  blink_function();
  delay(5000);
}
