#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include "../pins.h"


void turnLightOnOff(String color, String state){
  WebSerial.println(touchRead(32));
  if(state == "ON"){
    digitalWrite(output[color],HIGH);
  } else if(state == "OFF"){
    digitalWrite(output[color],LOW);
  }
}

void onWsEvent(AsyncWebSocket *server,AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch(type){
    case WS_EVT_CONNECT:{
      WebSerial.println("WS event connect");
      break;
    }
    case WS_EVT_DISCONNECT:{
      WebSerial.println("WS event disconnect");
      break;
    }
    case WS_EVT_DATA:{
      AwsFrameInfo *info =(AwsFrameInfo *)arg;
      if(info->final && info->index==0 && info->len ==len){
        if(info->opcode==WS_TEXT){
          String message = "";
          for (size_t i = 0; i < len; i++) {
            message += (char)data[i];
          }
          String parts[2];
          int commaIndex = message.indexOf(',');
          String color = message.substring(0, commaIndex);
          String state = message.substring(commaIndex + 1);
          turnLightOnOff(color, state);
        }
      }
      break;
    }
    case WS_EVT_PONG:{
      break;
    }

    case WS_EVT_ERROR:{
      break;
    }
  }
}