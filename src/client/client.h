#ifndef CLIENT_H
#define CLIENT_H

extern void startServer(AsyncWebServer &server);
extern void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
#endif