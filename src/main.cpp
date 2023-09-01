#include <Arduino.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include "ota/ota.h"
#include "wifi/wifi.h"
#include "client/client.h"
#include "routers/routers.h"
#include "pins.h"
#include "SPIFFS.h"
#include "memory.h"
#include "listData/listData.h"
#include <stdlib.h>

AsyncWebServer server(777);
AsyncWebSocket ws("/ws");

int pos = 0;
long stringToLong(String s)
{
    char arr[12];
    s.toCharArray(arr, sizeof(arr));
    return atol(arr);
}

int analog(int pin){
  float x= analogRead(pin);
  float y = 0.0000000000000000023212*x*x*x*x*x*x 
            -0.000000000000023614*x*x*x*x*x
            +0.000000000064187*x*x*x*x
            +0.000000023203*x*x*x
            -0.00030247*x*x
            +0.37845*x
            +47.75;
  
  return x+y;
}
void recvMsg(uint8_t *data, size_t len){
  String d = "";
  long number;
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  float ruido = 0;
  for(int i=0; i<20;i++){
    ruido+= analog(35);
    delay(10);
  }
  ruido = ruido/20;
  ruido = ruido/1289;
  WebSerial.print(ruido, 2);
  WebSerial.println("v");
  Serial.print(ruido, 2);
  Serial.println("v");
}



void setup() {
  Serial.begin(115200);
  memoryUsage();
  // Initialize the output variables as outputs
  pinMode(output["green"], OUTPUT);
  pinMode(output["red"], OUTPUT);
  pinMode(output["blue"], OUTPUT);
  // Set outputs to LOW
  digitalWrite(output["green"], LOW);
  digitalWrite(output["red"], LOW);
  digitalWrite(output["blue"], LOW);

  wifiStart();
  WebSerial.begin(&server);
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  WebSerial.msgCallback(recvMsg);
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  routers(server);
  server.begin();
  runOta();
}

int last = 100;
float oi = 0;
void loop(){
  float valores[20][2];
  int touch = touchRead(32);
  int ruido = analogRead(35);
  listPush(&lista,oi,touch,ruido,2.0);
  delay(10);
  oi++;
  if(touch<30 && last>=30){
    if(digitalRead(output["blue"])==HIGH){
      digitalWrite(output["blue"], LOW);
    }else{
      digitalWrite(output["blue"], HIGH);
    }
  }
  last = touch;
  /*for(int i=0;i<20;i++){
    float valor = analogRead(34);
    float temp = 43-((valor/110)*4);
    float tensao = analogRead(35)/1325.2;
    valores[i][0]=temp;
    valores[i][1]=tensao;
    delay(250);
  }
  float temp2 = 0.0;
  float tensao2 = 0.0;
  for(int i=0; i<20;i++){
    temp2 += valores[i][0];
    tensao2 += valores[i][1];
  }
  temp2 = temp2/20.0;
  tensao2 = tensao2/20.0;
  WebSerial.print(temp2, 1);
  WebSerial.print("C     ");
  WebSerial.print(tensao2, 2);
  WebSerial.println("V");*/
  startOta();
}