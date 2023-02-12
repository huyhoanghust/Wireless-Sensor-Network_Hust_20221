#include <PubSubClient.h>
#include <connect_wifi.h>
#include <cstring>
#include <string>

String clientId = "Device02"; 

#define MQTT_SERVER "broker.mqttdashboard.com"
#define MQTT_PORT 1883

#define MQTT_NODE_TEMP_PUB "Project/temp_pub"
#define MQTT_NODE_TEMP_SUB "Project/temp_sub"

#define MQTT_NODE_HUMI_PUB "Project/humi_pub"
#define MQTT_NODE_HUMI_SUB "Project/humi_sub"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

// void connect_to_broker();
// void callback(char *topic, byte *payload, unsigned int length);
void connect_to_broker()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // String clientId = "ESP32";
    // clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), "EmbeddedDev", "Ed12345678"))
    {
      Serial.println("connected");
      client.subscribe(MQTT_NODE_TEMP_SUB);
      client.subscribe(MQTT_NODE_HUMI_SUB);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}
