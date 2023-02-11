#include <Arduino.h>
#include <mqtt.h>
#include <remote.h>

#define sensor  35
#define relay 16
int count1 = 0;
enum
{
  fixed,
  notfix
};

int fix; 

int val_sensor;

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

  if (strcmp(topic, MQTT_NODE_LIGHT_SUB) == 0)
  {
    Serial.println("OK topic");
    if(strcmp(status, "ON") == 0)
    {
      digitalWrite(relay, LOW);
      Serial.println("relay on");
    }
    if(strcmp(status, "OFF") == 0)
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
  irrecv.enableIRIn(); // Start the receiver
  pinMode(relay, OUTPUT);
}

void loop()
{
  //Read analog light sensor
  char buf[10] = {0};
  val_sensor = analogRead(sensor);
  count1 ++;
  if (count1 == 5)
  {
    sprintf(buf, "%d", val_sensor);
    Serial.print("Value of light sensor: ");
    Serial.println(buf);
    client.publish(MQTT_NODE_LIGHT_PUB, buf);
    count1 = 0;
  }
  if(val_sensor < 1000)
  {
    Serial.println("Led OFF");
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
    Serial.println("Led ON");
  }
  client.loop();
  if (!client.connected())
  {
    connect_to_broker();
  }
  delay(500);
}