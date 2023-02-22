#include <Arduino.h>
#include <stdlib.h>
#include <mqtt.h>
#include <ds18b20.h>
#include <ota.h>

#define relay 2
#define pin_adc 33
#define led_1 25
#define led_2 26
#define led_3 27
#define resolutions 4095
unsigned long last_time = 0;
unsigned long delay_time = 2000;
// param of thresh temperature
RTC_DATA_ATTR float param1 = 30.0;
RTC_DATA_ATTR float param2 = 20.0;

int val_adc;
float percent;

#define uS_TO_S_FACTOR 1000000 // biến chuyển từ micro giây sang giây
#define TIME_TO_SLEEP 16       // Thời gian thức dậy

hw_timer_t *timer = NULL;
volatile bool flag = false;

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
  Serial.println(status);

  if (strcmp(topic, MQTT_NODE1_SUB_PARAM1) == 0)
  {
    param1 = atof(status);
  }
  if (strcmp(topic, MQTT_NODE1_SUB_PARAM2) == 0)
  {
    param2 = atof(status);
  }
  memset(status, '\0', sizeof(status));
  memset(payload, '\0', sizeof(payload));
}

void alarm(float temp)
{
  if (temp >= param1)
  {
    Serial.println("hot");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
  }
  if (temp > param2 && temp < param1)
  {
    Serial.println("Nomal");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, HIGH);
  }
  if (temp <= param2)
  {
    Serial.println("cold");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
  }
}

void read_adc()
{
  char buf[10] = {0};
  // val_adc = analogRead(pin_adc);
  // Serial.println(val_adc);
  // percent = val_adc * 100 / resolutions;
  percent = 68.1;
  sprintf(buf, "%.1f", percent);
  Serial.print("Percent pin: ");
  Serial.print(percent);
  Serial.println("%");
  //client.publish(MQTT_NODE1_PUB_ADC, buf);
}

void read_ds18b20()
{
  // read sensor
  char buf[10] = {0};
  sensors.requestTemperatures();
  //float temperatureC = sensors.getTempCByIndex(0);
  // display led
  float temperatureC = 25.1;
  alarm(temperatureC);
  sprintf(buf, "%.2f", temperatureC);
  Serial.print(temperatureC);
  Serial.println("ºC");
  // publish value temp on Broker
  //client.publish(MQTT_NODE1_PUB_SENSOR, buf);
}

void IRAM_ATTR callback_sleep()
{
  timerStop(timer);
  flag = true;
  Serial.println("sleep");
  esp_deep_sleep_start();
}

void start_timer()
{
  // config timer
  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(1, 80, true);
  /* Attach callback_sleep function to our timer */
  timerAttachInterrupt(timer, &callback_sleep, true);
  /* Set alarm to call callback_sleep function every second 1 tick is 1us
  => 4 second is 4000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 4000000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}

void wakeup()
{
  // esp_sleep_wakeup_cause_t wakeup_reason;
  // wakeup_reason = esp_sleep_get_wakeup_cause();
  Serial.println("Device Wakeup!");
  read_ds18b20();
  delay(1000);
  read_adc();
  delay(1000);
  update_FOTA();
  client.loop();
  if (!client.connected())
  {
    connect_to_broker();
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(500);
  //start_timer();
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  // sensors.begin();
  setup_wifi();
  Serial.print("Ver: ");
  Serial.println(version);
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();
  Serial.println("Start transfer");
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
}

void loop()
{
  wakeup();
}
