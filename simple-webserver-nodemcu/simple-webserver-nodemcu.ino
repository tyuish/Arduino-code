
 /*
 *  NodeMCU ESP8266 WEBSERVER
 * 
*/

const int refresh=3;//3 seconds
float tValue;// 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef STASSID
#define STASSID "TP-Link_3F0C" // Your WiFi SSID
#define STAPSK  "05205929" //Your WiFi password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);


void sendTemp() {
  String page = "<!DOCTYPE html><meta http-equiv='refresh' content='3'/><html><body><p>";
  page += String(tValue, 2);
  page +="</p></body></html>";  
  server.send(200,  "text/html",page);
}

void handleNotFound() {
  String message = "File Not Found. URI:";
  message += server.uri();
  server.send(404, "text/plain", message);
}

void setup(void) {
 
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", sendTemp);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
 tValue = rand();
 
  delay(300);// change this to larger value (1000 or more) if you don't need very often reading
}
