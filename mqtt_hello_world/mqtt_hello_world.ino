//Connects to Wifi and sends string message ("hi") to MQTT broker

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";
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
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

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
