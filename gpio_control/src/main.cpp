#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

char ssid[] = "";
char pass[] = "";
//String status = "";
int status = WL_IDLE_STATUS;
#define TOKEN "ESP8266_DEMO_TOKEN"
#define GPIO0 0
#define GPIO2 2

#define GPIO0_PIN 3
#define GPIO2_PIN 5

char thingsboardServer[] = "demo.thingsboard.io";
WiFiClient client;
HTTPClient http;
boolean gpioState[] = {false, false};
String get_gpio_status();
void set_gpio_status(int pin, boolean enabled);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Set output mode for all GPIO pins
  pinMode(GPIO0, OUTPUT);
  pinMode(GPIO2, OUTPUT);
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
  if(WiFi.status()==WL_CONNECTED){
    Serial.print("[HTTP] BEGIN...\n");
    http.begin(client, "http://demo.thingsboard.io/api/v1/QkQJbCLWJSskhzTiajsA/rpc");
    //http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] ... code: %d\n", httpCode);
    //const String& payload = http.getString("");
    if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
        on_message(payload,strlen(payload));
        //StaticJsonBuffer<200> jsonBuffer;
        //JsonObject& data = jsonBuffer.parseObject((char*)payload);

      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
    delay(10000); 
}
void on_message(byte* payload, unsigned int length){
  Serial.println("On message");
  char json[length+1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';
  Serial.print("Message: ");
  Serial.println(json);

  //Decode JSON request
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject((char*)json);
  if (!data.success())
  {
    Serial.println("parseObject() failed");
    return;
  }

  // Check request method
  String methodName = String((const char*)data["method"]);
  if (methodName.equals("getGpioStatus")) {
    // Reply with GPIO status
    //String responseTopic = String(topic);
    //responseTopic.replace("request", "response");
    //client.publish(responseTopic.c_str(), get_gpio_status().c_str());
    http.POST(get_gpio_status().c_str());
  } else if (methodName.equals("setGpioStatus")) {
    // Update GPIO status and reply
    set_gpio_status(data["params"]["pin"], data["params"]["enabled"]);
    //String responseTopic = String(topic);
    //responseTopic.replace("request", "response");
    //http.POST(get_gpio_status().c_str());
    http.begin(client, "http://demo.thingsboard.io/api/v1/QkQJbCLWJSskhzTiajsA/attributes");
    http.POST(get_gpio_status().c_str());
    //client.publish(responseTopic.c_str(), get_gpio_status().c_str());
    //client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
  }
}
String get_gpio_status() {
  // Prepare gpios JSON payload string
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  data[String(GPIO0_PIN)] = gpioState[0] ? true : false;
  data[String(GPIO2_PIN)] = gpioState[1] ? true : false;
  char payload[256];
  data.printTo(payload, sizeof(payload));
  String strPayload = String(payload);
  Serial.print("Get gpio status: ");
  Serial.println(strPayload);
  return strPayload;
}

void set_gpio_status(int pin, boolean enabled) {
  if (pin == GPIO0_PIN) {
    // Output GPIOs state
    digitalWrite(GPIO0, enabled ? HIGH : LOW);
    // Update GPIOs state
    gpioState[0] = enabled;
  } else if (pin == GPIO2_PIN) {
    // Output GPIOs state
    digitalWrite(GPIO2, enabled ? HIGH : LOW);
    // Update GPIOs state
    gpioState[1] = enabled;
  }
}