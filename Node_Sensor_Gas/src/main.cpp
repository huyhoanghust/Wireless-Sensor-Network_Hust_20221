#include <Arduino.h>
#include <mqtt.h>

#define sensor 34
#define relay 16

unsigned long last_time = 0;
unsigned long delay_time = 1000;

int value;

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

  if (strcmp(topic, MQTT_NODE_GAS_SUB) == 0)
  {
    Serial.println("OK topic");
    if (strcmp(status, "ON") == 0)
    {
      digitalWrite(relay, LOW);
      Serial.println("relay on");
    }
    if (strcmp(status, "OFF") == 0)
    {
      digitalWrite(relay, HIGH);
      Serial.println("relay off");
    }
  }
  memset(status, '\0', sizeof(status));
  memset(payload, '\0', sizeof(payload));
}

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();
  pinMode(relay, OUTPUT);
  digitalWrite(relay,HIGH);
}

void loop()
{

  if (millis() - last_time > delay_time)
  {
    value = analogRead(sensor);
    char buf_gas[10] = {0};
    sprintf(buf_gas,"%d",value);
    Serial.println(buf_gas);
    if(value>1800)
    {
      Serial.println("Gas leak!!!!");
      digitalWrite(relay,HIGH);
    }
    else
    {
      Serial.println("No Gas, it's OKE");
      digitalWrite(relay,LOW);
    }
    client.publish(MQTT_NODE_GAS_PUB,buf_gas);
    last_time = millis();
  }
  client.loop();
  if (!client.connected())
  {
    connect_to_broker();
  }
  delay(500);
}