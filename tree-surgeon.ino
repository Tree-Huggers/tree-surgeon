
/*
Made by Karo
A program to send data from sensors to webpage  via websocket using ESP32
The SPIFF library (SPI Flash File System) is utilised to do this
*/

#define MOISTURE_PIN 4 
//vcc pin on esp32 for water level sensor
#define POWER_PIN  17
//connected to water level sensor signal
#define SIGNAL_PIN A0

//temp + humidity
#define DHTPIN 21
//declare dht11 type of temp sensor
#define DHTTYPE DHT11


#include "DHT.h"
#include "WiFi.h"
#include "SPIFFS.h"
#include "AsyncTCP.h"
#include <FS.h>
#include <ESPAsyncWebServer.h>

//Finding IP address
const char* ssid = "VM4659135";
const char* password = "PNFBDCSLCC";
/*
I created a placeholder in the html for text replacement
For the async web server, the placeholder is held between percentage signs “%”
HTML code is taken as a constant string so it is stored in flash memory
*/
const char * html = "<p>%STATE1%</p>";
//Object is created to configure routes. Port 80 is default for HTTP
AsyncWebServer server(80);
 
//processor function that recieves template and replaces it with sensor values
String processor(const String& var)
{
  Serial.println(var);
 
  if(var == "STATE1")
    return "moisture_level";
    
  
  if(var == "STATE2")
    return "temperature";
    
  if(var == "STATE3")
    return "water_level";
    
 /* if(var == "PLACEHOLDER")
    return "n/a";
 */
 
  return String();
}
 
void setup(){
  //start serial transmission
  Serial.begin(115200);

  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW);

  WiFi.begin(ssid, password);
 
  //While waiting for wifi to be connected...
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
 //print the IP that has been assigned to serial monitor
  Serial.println(WiFi.localIP());
 
 //configure a route called 'website-request', it is listening for HTTP GET requests
  server.on("/website-request", HTTP_GET, [](AsyncWebServerRequest *request){
    /*
    send_P is used to return status code, the content-type, the content and template processor
    200 is the OK status code
    */
    request->send_P(200, "text/html", html, processor);
  });
 
  server.begin();
}
void loop(){
  
  //water level
  int water_level;
  digitalWrite(POWER_PIN, HIGH);  
  delay(100);                     
  value = analogRead(SIGNAL_PIN); 
  digitalWrite(POWER_PIN, LOW);   
   Serial.print("Water Level: ");
  Serial.println(water_level);
  delay(1000);

  //moisture level
  float moisture_level = analogRead(MOISTURE_PIN);
  Serial.println(moisture_level);
  delay(10000);

  //temp + humidity
  // read humidity
  float humidity  = dht.readHumidity();
  
  // making sure that no errors occured
  if (isnan(humidity)) {
    Serial.println("Error occured");
  } else {
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("%");
  }
 }
