
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <ArduinoJson.h>


#include <dht11.h>
dht11 DHT11; // create object of DHT11
#define dhtpin 14 // set the pin to connect to DHT11


ESP8266WiFiMulti WiFiMulti;
String mainURL ="http://192.168.0.102:8080/iot/data.php?";
String user="user=shyam5";
float temperature=45.3;
char type='j';

using namespace std;
String LS = "OFF";

void setup() {
 pinMode(12, OUTPUT); // PIN 12 LED on blink board
  Serial.begin(115200);
  //Serial.begin(74880);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("TP-Link_3F0C", "05205929");

}

void loop() {

 DHT11.read(dhtpin);// initialize the reading
  //code for Robojax.com video
  int humidity = DHT11.humidity;// get humidity
  int temp = getTemp('C');
  
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...");
    if (http.begin(client, mainURL+user+"&temp="+temp+"&humidity="+humidity)) {  // HTTP


      Serial.print("[HTTP] GET...");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {

          
          String payload = http.getString();
          Serial.println(payload);
          Serial.println("  ");
          
          // TODO: Parsing
          //const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
         // DynamicJsonBuffer jsonBuffer(bufferSize);
          //JsonObject& root = jsonBuffer.parseObject(http.getString());

        DynamicJsonDocument root(1024);
        deserializeJson(root, http.getString());

          // Parameters received
          int id = root["id"]; // 1
          const char* name = root["name"]; // "Leanne Graham"
          const char* username = root["username"]; // "Bret"
          const char* email = root["email"]; // "Sincere@april.biz"
          
          // Output to serial monitor
          Serial.print("Name:");
          Serial.println(name);
         Serial.print("Username:");
         Serial.println(username);
          Serial.print("Email:"); 
          Serial.println(email);
          string checker = "shyam";

if( username == checker){  Serial.println("Found Shyam in response.."); 
String ledstatus = "OFF";
if ( LS == ledstatus) {   Serial.print("It is off .."); LS = "ON";   digitalWrite(12, HIGH);  }

} else {
  LS = "OFF";   digitalWrite(12, LOW);
  
}



           
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect");
    }
  }

  delay(50);
}



   /*
 * getTemp(char type)
 * type character of upper case 
 * C is used to get Celsius
 * F is used to get fahrenheit
 * K is used for Kelvin
 */
float getTemp(char type) {
    float temp = (float)DHT11.temperature;//get temp
  if(type =='F')
  {
    return temp * 1.8 + 32;// convert to fahrenheit
  }else if(type =='K')
  {
    return temp + 274.15;// convert to Kelvin
  }else{
   return temp; 
  }
  
}
