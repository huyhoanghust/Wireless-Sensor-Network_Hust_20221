#include <Arduino.h>
#include <mqtt.h>
#include <DHT.h>

#define DHTPIN 22
#define relay 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long last_time = 0;
unsigned long delay_time = 5000;

float temp;
float humi;

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

  if (strcmp(topic, MQTT_NODE_TEMP_SUB) == 0)
  {
    Serial.println("OK topic temp");
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
  if (strcmp(topic, MQTT_NODE_HUMI_SUB) == 0)
  {
    Serial.println("OK topic humi");
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
  dht.begin();
  pinMode(relay, OUTPUT);
  digitalWrite(relay,HIGH);
}

void loop()
{
  if (millis() - last_time > delay_time)
  {
    char buf_temp[10] = {0};
    char buf_humi[10] = {0};
    // Read analog light sensor
    humi = dht.readHumidity();
    // Read temperature as Celsius (the default)
    temp = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    sprintf(buf_humi, "%.1f", humi);
    sprintf(buf_temp, "%.1f", temp);
    Serial.println(buf_humi);
    Serial.println(buf_temp);
    // Check if any reads failed and exit early (to try again).
    if (isnan(humi) || isnan(temp))
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    client.publish(MQTT_NODE_TEMP_PUB, buf_temp);
    delay(100);
    client.publish(MQTT_NODE_HUMI_PUB, buf_humi);
    last_time = millis();

  }

  client.loop();
  if (!client.connected())
  {
    connect_to_broker();
  }
  delay(500);
}