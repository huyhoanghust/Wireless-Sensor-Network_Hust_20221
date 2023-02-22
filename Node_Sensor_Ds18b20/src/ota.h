#include <HTTPUpdate.h>

String version = "0.9";
String key = "b893b3b9-90e5-4f5f-88da-8164555583a3";
String getChipId = "05";
void update_FOTA()
{
  Serial.println("check update!");
  String url = "http://otadrive.com/deviceapi/update?";
  url += "k=" + key;
  url += "&v=" + version;
  url += "&s=" + getChipId; // định danh thiết bị trên Cloud
 
  WiFiClient client;
  httpUpdate.update(client, url, version);
}