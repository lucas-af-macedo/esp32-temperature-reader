#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include "../../client/client.h"
#include "SPIFFS.h"
#include "../../pins.h"
#include "../../listData/listData.h"
#include <ArduinoJson.h>

String getPinState(int output){
  if(digitalRead(output)){
    return "ON";
  }
  else{
    return "OFF";
  }
}
void sendCsv(AsyncWebServerRequest *request){
  AsyncResponseStream *response = request->beginResponseStream("text/csv");
  response->addHeader("Content-Disposition", "attachment; filename=data.csv");

  struct data *current = lista.firstData; // Preencha com sua lista de dados
    while (current != NULL) {
        char csvLine[100];  // Ajuste o tamanho conforme necessário
        snprintf(csvLine, sizeof(csvLine), "%.2f,%.2f,%.2f,%.2f\n",
                 current->temperature1, current->temperature2,
                 current->voltage, current->current);
        response->print(csvLine);
        current = current->next;
    }

    request->send(response);
}

void sendCali(AsyncWebServerRequest *request){
  AsyncResponseStream *response = request->beginResponseStream("text/csv");
  response->addHeader("Content-Disposition", "attachment; filename=data.csv");
 // Preencha com sua lista de dados
    for (int i = 0; i<100; i++) {
        char csvLine[100];  // Ajuste o tamanho conforme necessário
        snprintf(csvLine, sizeof(csvLine), "%.2f,%.2f\n",
                 array[i][0], array[i][1]);
        response->print(csvLine);
    }

    request->send(response);
}
void getData(AsyncWebServerRequest *request){
    WebSerial.println("Requisitando dados...");
    
    DynamicJsonDocument jsonDocument(1024);
    JsonArray jsonArray = jsonDocument.to<JsonArray>();
    for (const auto& kv : output){
        JsonArray row = jsonArray.createNestedArray();
        row.add(kv.first);
        row.add(getPinState(kv.second));
        row.add(kv.second);
    }
    String jsonResponse;
    serializeJson(jsonArray, jsonResponse);
    request->send(200, "application/json", jsonResponse);
}

void getHtml(AsyncWebServerRequest *request){
    WebSerial.println("Requesting index page...");
    request->send(SPIFFS, "/index.html", "text/html",false);
}


