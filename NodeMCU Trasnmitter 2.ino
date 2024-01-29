#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>



// WiFi parameters to be configured
const char* ssid = "knight"; // Write here your router's username
const char* password = ""; // Write here your router's passward
ESP8266WebServer server(80);

String command;  

void setup(void){

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     digitalWrite(LED_BUILTIN, LOW);
     delay(500);
     Serial.print(".");
     digitalWrite(LED_BUILTIN, HIGH);
     delay(100);
  }
  //print a new line, then print WiFi connected and the IP address
  //Serial.println("");
  //Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);

  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin(); 

}
void loop() {
  // Nothing

  server.handleClient();


      command = server.arg("State");
}


void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
      
      command = server.arg("State");
      Serial.println(server.arg("State"));

      
      
      
  }
  server.send ( 200, "text/html", "The BOT" );
  delay(1);
}
