#include <Arduino.h>
#include <cloud.h>
#include <mqtt.h>
#include <ota.h>
#include <string.h>

unsigned long last_time = 0;
unsigned long delay_time = 1000;

void callback(char *topic, byte *payload, unsigned int length)
{
  char status[50] = {0};
  String rc = clientId + " receive new message from broker";
  Serial.println(rc);
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");
  Serial.write(payload, length);
  Serial.println();
  // Serial.println((char*)payload);
  for (int i = 0; i < length; i++)
  {
    status[i] = (char)payload[i];
  }
  // strcpy(status, (char*) payload);
  Serial.print("Message is: ");
  Serial.println(status);
  // check topic
  if (strcmp(topic, MQTT_NODE1_PUB_SENSOR) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.node1, status);
  }
  if (strcmp(topic, MQTT_NODE2_PUB_SENSOR) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.node2, status);
  }
  if (strcmp(topic, MQTT_NODE3_PUB_SENSOR) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.node3, status);
  }
  if (strcmp(topic, MQTT_NODE4_PUB_SENSOR) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.node4, status);
  }
  if (strcmp(topic, MQTT_NODE5_PUB_SENSOR) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.node5, status);
  }
  // ADC
  if (strcmp(topic, MQTT_NODE1_PUB_ADC) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.pin1, status);
  }
  if (strcmp(topic, MQTT_NODE2_PUB_ADC) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.pin2, status);
  }
  if (strcmp(topic, MQTT_NODE3_PUB_ADC) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.pin3, status);
  }
  if (strcmp(topic, MQTT_NODE4_PUB_ADC) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.pin4, status);
  }
  if (strcmp(topic, MQTT_NODE5_PUB_ADC) == 0)
  {
    thingboard_gate_send(Cloud_method_receive.pin5, status);
  }
  memset(status, '\0', sizeof(status));
  memset(payload, '\0', sizeof(payload));
}

void thingboard_gate_receive()
{
  // http.addHeader("Content-Type", "application/json");
  // Serial.print("[HTTP] BEGIN...\n");
  http.begin(clienthttp, "http://thingsboard.cloud/api/v1/dlN4nUZmFL5afj9OGn7a/rpc");
  // Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    // status_code :(code =200 => success) (404: not find) (400 bad request) (500: server error) (502 bad gateway)
    Serial.printf("Status server: %d\n", httpCode);
    // const String& payload = http.getString("");
    if (httpCode == HTTP_CODE_OK)
    {
      const String &payload = http.getString();
      Serial.println("received payload:");
      Serial.println(payload);
      Serial.println(">>");
      // declare name have 100bytes memory to store Payload
      DynamicJsonDocument read(100);
      deserializeJson(read, payload);
      // Read value of payload
      String id = read["id"].as<String>();
      String method = read["method"].as<String>();
      String param = read["params"].as<String>();
      Serial.println(id);
      Serial.println(method);
      Serial.println(param);
      // check method of payload
      // if method is correct, Gate publish message to a topic of Broker, which nodes recieve message
      // check payload DS18b20
      if (method == Cloud_method_send.threshold1)
      {
        client.publish(MQTT_NODE1_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE2_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE3_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE4_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE5_SUB_PARAM1, param.c_str());
      }
      if (method == Cloud_method_send.threshold2)
      {
        client.publish(MQTT_NODE1_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE2_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE3_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE4_SUB_PARAM1, param.c_str());
        delay(100);
        client.publish(MQTT_NODE5_SUB_PARAM1, param.c_str());
      }
    }
    else
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  }
}
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(500);
  Serial.print("Version: ");
  Serial.println(version);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();
  // thingboard_gate_receive();
  //  Serial.println("Start transfer");
}

void loop()
{
  // if(millis() - last_time > delay_time)
  // {
  //   thingboard_gate_receive();
  //   last_time = millis();
  // }
  // thingboard_gate_receive();
  client.loop();
  if (!client.connected())
  {
    connect_to_broker();
  }
}