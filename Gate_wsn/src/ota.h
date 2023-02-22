#include <HTTPUpdate.h>

uint32_t updateCounter = 0;
String version = "1.0";
String key = "b893b3b9-90e5-4f5f-88da-8164555583a3";
String getChipId = "Gate";
void update_FOTA()
{
  String url = "http://otadrive.com/deviceapi/update?";
  url += "k=" + key;
  url += "&v=" + version;
  url += "&s=" + getChipId; // định danh thiết bị trên Cloud
 
  WiFiClient client_ota;
  httpUpdate.update(client_ota, url, version);
}