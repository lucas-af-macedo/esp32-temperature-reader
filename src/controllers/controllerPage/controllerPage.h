#ifndef CONTROLLERPAGE_H
#define CONTROLLERPAGE_H
#include <ESPAsyncWebServer.h>

extern void getHtml(AsyncWebServerRequest *request);
extern void getData(AsyncWebServerRequest *request);
extern void sendCsv(AsyncWebServerRequest *request);
extern void sendCali(AsyncWebServerRequest *request);
#endif