/*
 * Contol a relay over WiFi using ESP8266 NodeMCU, D1 Mini to 
 * turn ON or OFF 2 AC bulb or 2 fan or other load using 2 channel relay
*/

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

int relay1Pin = D1;//define a pin for relay
int relay2Pin = D2;//define a pin for relay

int relay1State = 1;//initial state . 1 ON, 0 OFF
int relay2State = 1;//initial state . 1 ON, 0 OFF

String button1Title1 ="Light ON";
String button1Title2 ="Light OFF";

String button2Title1 ="Buzzer ON";
String button2Title2 ="Buzzer OFF";



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>



#ifndef STASSID
#define STASSID "TP-Link_3F0C" // your WiFi SSID
#define STAPSK  "05205929" //your WiFi password
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
 String HTML ="<!DOCTYPE html>\<html>\<head>\<title>Robojax ESP8266 Relay Control</title>\<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\<style>\html,body{width:100%\;height:100%\;margin:0}*{box-sizing:border-box}.colorAll{background-color:#90ee90}.colorBtn{background-color:#add8e6}.angleButtdon,a{font-size:30px\;border:1px solid #ccc\;display:table-caption\;padding:7px 10px\;text-decoration:none\;cursor:pointer\;padding:5px 6px 7px 10px}a{display:block}.btn{margin:5px\;border:none\;display:inline-block\;vertical-align:middle\;text-align:center\;white-space:nowrap}";
  HTML +="</style></head><body><h1>Robojax ESP8266 2 ch Relay Control </h1>";
  
  if(relay1State){
    HTML +="<div class=\"btn\"><a class=\"angleButton\" style=\"background-color:#f56464\"  href=\"/control?r1=off\">";
    HTML +=button1Title2;  
  }else{
    HTML +="<div class=\"btn\"><a class=\"angleButton \" style=\"background-color:#90ee90\"  href=\"/control?r1=on\">";
    HTML +=button1Title1;      
  }
  HTML +="</a></div>";
  
  if(relay2State){
    HTML +="<div class=\"btn\"><a class=\"angleButton\" style=\"background-color:#f56464\"  href=\"/control?r2=off\">";
    HTML +=button2Title2;  
  }else{
    HTML +="<div class=\"btn\"><a class=\"angleButton \" style=\"background-color:#90ee90\"  href=\"/control?r2=on\">";
    HTML +=button2Title1;    
  }  
  HTML +="</a></div></body></html>";
  server.send(200, "text/html", HTML);  
}//handleRoot()

void handleNotFound() {

  String message = "File Not Found";
  message += "URI: ";
  message += server.uri();
  message += "Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "Arguments: ";
  message += server.args();
  message += "";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + " ";
  }

  server.send(404, "text/plain", message);

}//end of handleNotFound()

void setup(void) {
  pinMode(relay1Pin, OUTPUT);// define a pin as output for relay
  digitalWrite(relay1Pin, relay1State);//initial state either ON or OFF

  pinMode(relay2Pin, OUTPUT);// define a pin as output for relay
  digitalWrite(relay2Pin, relay2State);//initial state either ON or OFF  
  
  Serial.begin(115200);//initialize the serial monitor

  //Relay control ON OFF by Robojax.com

    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: http://");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
    Serial.println("access it via http://esp8266");
  }

  server.on("/", handleRoot);
  server.on("/control", HTTP_GET, relayControl);         
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}//end of setup

void loop(void) {
  
  server.handleClient();
  MDNS.update();

  if(relay1State ==1)
  {
    digitalWrite(relay1Pin, LOW);
  }else
  {
    digitalWrite(relay1Pin, HIGH);
  }
  
  if(relay2State ==1)
  {
    digitalWrite(relay2Pin, LOW);
  }else{
    digitalWrite(relay2Pin, HIGH);    
  }

   delay(100);
   //Serial.print("Relay1:");Serial.print (relay1State);
   //Serial.print(" Relay2:");Serial.println(relay2State);   
}//end of loop

/*
 * relayControl()
 * updates the value of "relayState" varible to 1 or zero 
 * returns nothing
 * written by Ahmad Shamshiri
 * on Wednesday Feb 22, 2020 at 16:20 in Ajax, Ontario, Canada
 * www.robojax.com
 */
void relayControl() {
  if(server.arg("r1") == "on")
  {
    relay1State = 1;// set state of relay1 to ON
  }else if(server.arg("r1") == "off"){
    relay1State = 0;  // set state of relay1 to OFF
  }
  
  if(server.arg("r2") == "on") {
    relay2State =1; // set state of relay2 to ON  
  }else if(server.arg("r2") == "off"){
    relay2State =0;  // set state of relay2 to OFF
  }

  handleRoot();
}//relayControl() end
