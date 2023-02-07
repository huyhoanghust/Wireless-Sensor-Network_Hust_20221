#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

char ssid[] = "FPT BACH KHOA";
char pass[] = "abc13579";
int status = WL_IDLE_STATUS;
int smokeA0 = A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    delay(10000);
  }
  Serial.println("");
  Serial.println("Da ket noi Wifi");
}

void loop() {
  // put your main code here, to run repeatedly:
  String value = "25";
  int analogSensor = analogRead(smokeA0);
    Serial.print("Pin A0: ");
    Serial.println(analogSensor);
    if(WiFi.status()==WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      String postData = "{\"value\": " + value + "}";
      Serial.print("[HTTP] BEGIN...\n");
      http.begin(client, "http://demo.thingsboard.io/api/v1/QkQJbCLWJSskhzTiajsA/telemetry");
      http.addHeader("Content-Type", "application/json");
      Serial.print("[HTTP] POST...\n");
      int httpCode = http.POST(postData);
      if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    }
    delay(10000);
}