#include <ESPAsyncWebServer.h>
#include "../client/client.h"
#include "SPIFFS.h"
#include "routerPage/routerPage.h"

void routers(AsyncWebServer &server){
    routerPage(server);
    
    server.onNotFound([](AsyncWebServerRequest *request){
        request-> send(404,"text/plain","Not found");
    });
}