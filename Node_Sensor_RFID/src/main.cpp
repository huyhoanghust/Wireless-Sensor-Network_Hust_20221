#include <Arduino.h>
#include <mqtt.h>
#include <rfid.h>

#define relay 16
#define but_adc 14
#define pin_adc 33
#define led_1 25
#define led_2 26
#define led_3 27

volatile bool flag = false;

byte *ID;
int val_adc;

hw_timer_t *timer = NULL;

void off_led();

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

  if (strcmp(topic, MQTT_NODE_RFID_SUB) == 0)
  {
    if (strcmp(status, "Close_door") == 0)
    {
      Serial.println("Close the door");
      digitalWrite(relay, HIGH);
    }
    else if (strcmp(status, "Open_door") == 0)
    {
      Serial.println("Open the door");
      digitalWrite(relay, LOW);
    }
  }
  memset(status, '\0', sizeof(status));
  memset(payload, '\0', sizeof(payload));
}

void IRAM_ATTR read_adc_pin()
{
  flag = true;
}

void IRAM_ATTR timer_adc()
{
  Serial.println("All Led off");
  off_led();
  timerStop(timer);
  //   timer = NULL;
}

void off_led()
{
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
}

void start_timer()
{
  // config timer
  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  /* Attach timer_adc function to our timer */
  timerAttachInterrupt(timer, &timer_adc, true);
  /* Set alarm to call timer_adc function every second 1 tick is 1us
  => 3 second is 3000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 3000000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}

void check_value()
{
  if (val_adc < 100)
  {
    Serial.println("Low Pin");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
  }
  if (val_adc > 100 && val_adc < 160)
  {
    Serial.println("Nomal Pin");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, HIGH);
  }
  if (val_adc > 160)
  {
    Serial.println("Full Pin");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(500);
  // set up wifi
  setup_wifi();
  // setup mqtt config
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();
  Serial.println(F("Initialize System"));
  // init rfid D8,D5,D6,D7
  SPI.begin();
  rfid.PCD_Init();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();
  // config read adc pin
  pinMode(but_adc, INPUT_PULLUP);
  attachInterrupt(but_adc, read_adc_pin, CHANGE);
  // init timer
  start_timer();
  // config led display
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  off_led();
}

void loop()
{
  // RFID
  readRFID();
  switch (uidDec)
  {
  case Hoang:
    Serial.println("Relative!!");
    digitalWrite(relay, LOW);
    client.publish(MQTT_NODE_RFID_PUB, "The door was opened by Hoang");
    delay(4000);
    digitalWrite(relay, HIGH);
    client.publish(MQTT_NODE_RFID_PUB, "The door was closed");
    break;
  case Huy:
    Serial.println("Relative!!");
    digitalWrite(relay, LOW);
    client.publish(MQTT_NODE_RFID_PUB, "The door was opened by Huy");
    delay(4000);
    digitalWrite(relay, HIGH);
    client.publish(MQTT_NODE_RFID_PUB, "The door was closed");
    break;
  case Thanh:
    Serial.println("Relative!!");
    digitalWrite(relay, LOW);
    client.publish(MQTT_NODE_RFID_PUB, "The door was opened by Thanh");
    delay(4000);
    digitalWrite(relay, HIGH);
    client.publish(MQTT_NODE_RFID_PUB, "The door was closed");
    break;
  case anomynous:
    Serial.println("Relative!!");
    digitalWrite(relay, LOW);
    client.publish(MQTT_NODE_RFID_PUB, "The door was opened by anomynous");
    delay(4000);
    digitalWrite(relay, HIGH);
    client.publish(MQTT_NODE_RFID_PUB, "The door was closed");
    break;
  }
  uidDec = 0;
  // check adc pin
  if (flag)
  {
    val_adc = analogRead(pin_adc);
    Serial.println(val_adc);
    check_value();
    flag = false;
    Serial.println("Start timer");
    timerStart(timer);
  }
  // connect to broker
  client.loop();
  if (!client.connected())
  {
    connect_to_broker();
  }
}