// #include <connect_wifi.h>
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

// void thingboard_gate_receive()
// {
//   // http.addHeader("Content-Type", "application/json");
//   //Serial.print("[HTTP] BEGIN...\n");
//   http.begin(clienthttp, "http://demo.thingsboard.io/api/v1/y4n40TeUUqtpMDMt8MS9/rpc");
//   //Serial.print("[HTTP] GET...\n");
//   int httpCode = http.GET();
//   if (httpCode > 0)
//   {
//     // HTTP header has been send and Server response header has been handled
//     // status_code :(code =200 => success) (404: not find) (400 bad request) (500: server error) (502 bad gateway)
//     Serial.printf("Status server: %d\n", httpCode);
//     // const String& payload = http.getString("");
//     if (httpCode == HTTP_CODE_OK)
//     {
//       const String &payload = http.getString();
//       Serial.println("received payload:");
//       Serial.println(payload);
//       Serial.println(">>");
//       DynamicJsonDocument read(100);
//       deserializeJson(read, payload);
//       String id = read["id"].as<String>();
//       String method = read["method"].as<String>();
//       String param = read["params"].as<String>();
//       Serial.println(id);
//       Serial.println(method);
//       Serial.println(param);
//       if (method == Cloud_method.temperature)
//       {
//         if(param == state.ON)
//         {
          
//         } 
//         else if(param == state.OFF)
//         {

//         }
//       }
//       // StaticJsonBuffer<200> jsonBuffer;
//       // JsonObject& data = jsonBuffer.parseObject((char*)payload);
//     }
//     else
//     {
//       Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//     }
//   }
// }
void thingboard_gate_send(String method,String str)
{
  String postData = "{"+ method +": " + str + "}";
  //Serial.print("[HTTP] BEGIN...\n");
  http.begin(clienthttp, "http://demo.thingsboard.io/api/v1/TAUpxIgVr0ulCTGSZqFd/telemetry");
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

