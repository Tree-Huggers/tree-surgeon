

/*
Made by Karo
A program to send data from sensors to webpage  via websocket using ESP32
The SPIFF library (SPI Flash File System) is utilised to do this
*/

#include "SPIFFS.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

//Finding IP address
const char* ssid = "networkName;
const char* password = "networkPassword";

/*
I created a placeholder in the html for text replacement
For the async web server, the placeholder is held between percentage signs “%”
HTML code is taken as a constant string so it is stored in flash memory
*/

const char * html = "<p>%PLACEHOLDER%</p>";

//Object is created to configure routes. Port 80 is default for HTTP
AsyncWebServer server(80);
 
//processor function that recieves template and replaces it with sensor values
String processor(const String& var)
{
 
  Serial.println(var);
 
  if(var == "PLACEHOLDER")
    return "SENSOR VALUES";
 
  return String();
}
 
void setup(){
  //start serial transmission
  Serial.begin(115200);
 
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

//Time to open a serial connection so we can start to send data
void setup() {
  
  Serial.begin(115200);  
  if(!SPIFFS.begin(true)){
      Serial.println("Error: Sorry something went pear shaped! ");
      return;
  else:
  	
    File file = SPIFFS.open("/website");
      WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/test_file.html", "text/html");
  });

  server.begin();
}

void loop(){}

  }
}
