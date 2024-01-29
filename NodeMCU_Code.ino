#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>




String command;  
     

const char* ssid = "node"; // put WIFI SSID for creating AP     
const char* pass = ""; // put WIFI password for creating AP
ESP8266WebServer server(80);

//int RX = 3;
//int TX = 1;
//SoftwareSerial softwareSerial(1,3);




void setup() {

  

  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();   

}

void loop() {

  server.handleClient();


      command = server.arg("State");
      
      //if(command=="F") Serial.write()('F');
      //else if (command =="B") Serial.write('B');
      //else if(command =="L") Serial.write('L');
      //else if(command =="R") Serial.write('R');
      //else if(command =="S") Serial.write('S');
      //Serial.println(command);


  

}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
      
      command = server.arg("State");
      Serial.println(server.arg("State"));
      
      
  }
  server.send ( 200, "text/html", "The BOT" );
  delay(1);
}
