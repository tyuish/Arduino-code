/*
 * Display temperature using DHT11, DHT22 with NodeMCU ESP8266 with Arduino IDE
 * 
 * Watch video instruciton for this video: https://youtu.be/1A4-6hDARQc
 * 
 * I have combined DHT library of Adafruit with ESP8266 WebServer both links 
 * Adafruit DHT library on GitHub: https://github.com/adafruit/DHT-sensor-library
 * and 
 * ESP8266 on GitHub : https://github.com/esp8266/Arduino
 * 
*/

// @shyam: Some times we get nan using this new library for DHT11 sensors.. this did not happen with other library

// DHT settings starts
#include "DHT.h"
#define DHTPIN 14     // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

// ****** DHT settings end (Robojax.com )


void setup(void) {
  dht.begin();
  Serial.begin(115200);
}


void loop(void) {

  float c = dht.readTemperature();     // Read temperature as Celsius (the default)
  float h = dht.readHumidity();        // Reading humidity 
  float f = dht.readTemperature(true); // Read temperature as Fahrenheit (isFahrenheit = true)
  
  Serial.print(c);
  Serial.print("C    ");
  Serial.print(h);
  Serial.print("%    ");
  Serial.print(f);
  Serial.print("F");
  Serial.println();

  delay(300);// change this to larger value (1000 or more) if you don't need very often reading
  
}
