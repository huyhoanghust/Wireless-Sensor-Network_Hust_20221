#include <PubSubClient.h>
#include <connect_wifi.h>
#include <cstring>
#include <string>

String clientId = "Device00";

#define MQTT_SERVER "broker.mqttdashboard.com"
#define MQTT_PORT 1883

#define MQTT_NODE1_PUB_SENSOR "Project/node_01_pub_sensor"
#define MQTT_NODE1_PUB_ADC "Project/node_01_pub_adc"
#define MQTT_NODE1_SUB_PARAM1 "Project/node_01_sub_param1"
#define MQTT_NODE1_SUB_PARAM2 "Project/node_01_sub_param2"

#define MQTT_NODE2_PUB_SENSOR "Project/node_02_pub_sensor"
#define MQTT_NODE2_PUB_ADC "Project/node_02_pub_adc"
#define MQTT_NODE2_SUB_PARAM1 "Project/node_02_sub_param1"
#define MQTT_NODE2_SUB_PARAM2 "Project/node_02_sub_param2"

#define MQTT_NODE3_PUB_SENSOR "Project/node_03_pub_sensor"
#define MQTT_NODE3_PUB_ADC "Project/node_03_pub_adc"
#define MQTT_NODE3_SUB_PARAM1 "Project/node_03_sub_param1"
#define MQTT_NODE3_SUB_PARAM2 "Project/node_03_sub_param2"

#define MQTT_NODE4_PUB_SENSOR "Project/node_04_pub_sensor"
#define MQTT_NODE4_PUB_ADC "Project/node_04_pub_adc"
#define MQTT_NODE4_SUB_PARAM1 "Project/node_04_sub_param1"
#define MQTT_NODE4_SUB_PARAM2 "Project/node_04_sub_param2"

#define MQTT_NODE5_PUB_SENSOR "Project/node_05_pub_sensor"
#define MQTT_NODE5_PUB_ADC "Project/node_05_pub_adc"
#define MQTT_NODE5_SUB_PARAM1 "Project/node_05_sub_param1"
#define MQTT_NODE5_SUB_PARAM2 "Project/node_05_sub_param2"

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
      client.subscribe(MQTT_NODE1_PUB_SENSOR);
      delay(50);
      client.subscribe(MQTT_NODE2_PUB_SENSOR);
      delay(50);
      client.subscribe(MQTT_NODE3_PUB_SENSOR);
      delay(50);
      client.subscribe(MQTT_NODE4_PUB_SENSOR);
      delay(50);
      client.subscribe(MQTT_NODE5_PUB_SENSOR);
      delay(50);
      client.subscribe(MQTT_NODE1_PUB_ADC);
      delay(50);
      client.subscribe(MQTT_NODE2_PUB_ADC);
      delay(50);
      client.subscribe(MQTT_NODE3_PUB_ADC);
      delay(50);
      client.subscribe(MQTT_NODE4_PUB_ADC);
      delay(50);
      client.subscribe(MQTT_NODE5_PUB_ADC);
      delay(50);
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
