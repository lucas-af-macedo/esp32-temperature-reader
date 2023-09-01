#include <ESPAsyncWebServer.h>
#include "../../client/client.h"
#include "../../controllers/controllerPage/controllerPage.h"
#include "SPIFFS.h"

void routerPage(AsyncWebServer &server){
  server.on("/", HTTP_GET, getHtml);
  server.serveStatic("/css/", SPIFFS, "/css/");
  server.serveStatic("/script/", SPIFFS, "/script/");
  server.on("/data", HTTP_GET, getData);
  server.on("/test.csv", HTTP_GET, sendCsv);
  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");
}