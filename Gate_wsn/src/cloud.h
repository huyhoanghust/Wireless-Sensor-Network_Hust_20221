// #include <connect_wifi.h>
#include <HTTPClient.h>
#include <Wifi.h>
#include <ArduinoJson.h>
WiFiClient clienthttp;
HTTPClient http;

//{"id":60,"method":"nhietdo","params":true}
struct cloud
{
  String node1 = "node1";
  String node2 = "node2";
  String node3 = "node3";
  String node4 = "node4";
  String node5 = "node5";
  String pin1 = "pin1";
  String pin2 = "pin2";
  String pin3 = "pin3";
  String pin4 = "pin4";
  String pin5 = "pin5";
  String ota = "Ota";
  String threshold1 = "nguong1";
  String threshold2 = "nguong2";
};

struct states
{
  String ON = "true";
  String OFF = "false";
};
//cloud is origin
cloud Cloud_method_receive;
cloud Cloud_method_send;

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

