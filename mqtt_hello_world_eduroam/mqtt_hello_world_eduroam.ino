//Connects to Eduroam Wifi and sends string message to MQTT broker

#include "esp_wpa2.h"
#include <WiFi.h>
#include <PubSubClient.h>

String line; //variable for response
const char* ssid = "eduroam"; // Eduroam SSID
const char* host = "arduino.php5.sk"; //external server domain
#define EAP_IDENTITY "YourUsername@upatras.gr" // or @ your institution domain
#define EAP_PASSWORD "YourUPatrasPassword"
const char* mqttServer = "YourMQTTbrokerIP";
const int mqttPort = 1883;
const char* mqttUser = "YourMQTTBrokerUsername";
const char* mqttPassword = "YourMQTTBrokerPassword";
const char* topic = "YourTopic";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  String messageTemp;

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();
  if(messageTemp == "on"){
    digitalWrite(2, HIGH);
    Serial.println("Status: " + messageTemp);
  }
  if(messageTemp == "off"){
  digitalWrite(2, LOW);
  Serial.println("Status: "+ messageTemp);
}
  Serial.println();
  Serial.println("-----------------------");
}
void setup() {

  byte error = 0;
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect from wifi to set new wifi connection
  WiFi.mode(WIFI_STA);
  error += esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  error += esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  //error += esp_wifi_sta_wpa2_ent_set_new_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));  //First time running, i think i needed to set this, although i received an error from the server, claiming the password was not set?
  error += esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //Following times, it ran fine with just this line (connects very fast).
  if (error != 0) {
    Serial.println("Error setting WPA properties.");
  }
  WiFi.enableSTA(true);

  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  if (esp_wifi_sta_wpa2_ent_enable(&config) != ESP_OK) {
    Serial.println("WPA2 Settings Not OK");
  }

  WiFi.begin(ssid); //connect to Eduroam function
  WiFi.setHostname("RandomHostname"); //set Hostname for your device - not neccesary
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: ");
  Serial.println(WiFi.localIP()); //print LAN IP

  pinMode(2, OUTPUT);
  Serial.begin(115200);

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.subscribe(topic);
}

void loop() {
client.loop();
client.publish(topic, "Hello world from ESP32!");
delay(5000);
}
