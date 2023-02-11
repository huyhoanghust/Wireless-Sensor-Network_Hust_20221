#include <PubSubClient.h>
#include <connect_wifi.h>
#include <cstring>
#include <string>

String clientId = "Device01"; 

#define MQTT_SERVER "broker.mqttdashboard.com"
#define MQTT_PORT 1883

#define MQTT_NODE_RFID_PUB "Project/rfid_pub"
#define MQTT_NODE_RFID_SUB "Project/rfid_sub"

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
      client.subscribe(MQTT_NODE_RFID_SUB);
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

// void callback(char *topic, byte *payload, unsigned int length)
// {
//   char status[20] = {0};
//   Serial.println("-------new message from broker-----");
//   Serial.print("topic: ");
//   Serial.println(topic);
//   Serial.print("message: ");
//   Serial.write(payload, length);
//   Serial.println();
//   //Serial.println((char*)payload);
//   for (int i = 0; i < length; i++)
//   {
//     status[i] = (char)payload[i];
//   }
//   //strcpy(status, (char*) payload);
//   Serial.println(status);

//   if (strcmp(topic, MQTT_LED1_TOPIC) == 0)
//   {
//     Serial.println();
//     Serial.println("OK Topic");
//     client.publish(MQTT_LED1_TOPIC, "OKE");
//     if (strcmp(status, "OFFLED") == 0)
//     {
//       Serial.println("LED1 OFF");
//       digitalWrite(led, LOW);
//     }
//     else if (strcmp((char*)status, "ONLED") == 0)
//     {
//       Serial.println("LED1 ON"); 
//       digitalWrite(led, HIGH);
//     }
//   }
//   memset(status, '\0', sizeof(status));
//   memset(payload, '\0', sizeof(payload));
// }