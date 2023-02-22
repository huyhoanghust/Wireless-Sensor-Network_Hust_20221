/**
 * @file cloud.h
 * @author hoanghuyhust (hoangnh191855@sis.hust.edu.vn)
 * @brief 
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <HTTPClient.h>
#include <Wifi.h>
#include <ArduinoJson.h>
WiFiClient clienthttp;
HTTPClient http;

//{"id":60,"method":"nhietdo","params":true}
struct cloud
{
  String temperature = "Nhietdo";
  String gas = "Khigas";
  String light = "Anhsang";
  String humidity = "Doam";
  String RFID = "Rfid";
  String ota = "Ota";
};

struct states
{
  String ON = "true";
  String OFF = "false";
};

cloud Cloud_method;
states state;

void thingboard_gate_send(String method,String str)
{
  String postData = "{"+ method +": " + str + "}";
  //Serial.print("[HTTP] BEGIN...\n");
  http.begin(clienthttp, "http://thingsboard.cloud/api/v1/dlN4nUZmFL5afj9OGn7a/telemetry");
  http.addHeader("Content-Type", "application/json");
  Serial.println("[HTTP] POST MESSAGE");
  int httpCode = http.POST(postData);
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  }
  else
  {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
}

