/**
 * @file connect_wifi.h
 * @author hoanghuyhust (hoangnh191855@sis.hust.edu.vn)
 * @brief 
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <WiFi.h>
const char *ssid = "Zhuge Liang";
const char *password = "facebook";
// const char *ssid = "P514";
// const char *password = "514a62001";
int count = 0;
void setup_wifi()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    count++;
    if (count == 10)
    {
      WiFi.mode(WIFI_AP_STA);
      /* start SmartConfig */
      WiFi.beginSmartConfig();

      /* Wait for SmartConfig packet from mobile */
      Serial.println("Waiting for SmartConfig.");
      while (!WiFi.smartConfigDone())
      {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.println("SmartConfig done.");

      /* Wait for WiFi to connect to AP */
      Serial.println("Waiting for WiFi");
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}