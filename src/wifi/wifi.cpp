#include <WiFi.h>

const char* ssid = "Lucas";
const char* password = "mateus03";

void wifiStart(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode( WIFI_STA );
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}