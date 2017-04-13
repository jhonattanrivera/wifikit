#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>


// SSID Configuration
const char* ssid = ". . .";
const char* password = ". . .";

// static ip configuration
IPAddress ip(192,168,1,40);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

const char* response = "{\"status\": %d, \"code\": %d}";
char buffer[26];

// MDNSResponder mdns;

ESP8266WebServer server(80);

const int R1 = 0;
const int R2 = 2;





void handleNotFound(){
  String message = "Resource not found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleRelay(int relay, int level) {
  // change the state of the relay given the relay number and the level
  digitalWrite(relay, level);

  level ? level = 0 : level = 1;

  sprintf(buffer, response, level , 200);
  server.send(200, "application/json", buffer);
}

void statusRelay(int relay){
  // returns the status of the relay given the relay number
  int status;
  status = digitalRead(relay);

  status ? status = 0 : status = 1;

  sprintf(buffer, response, status, 200);
  server.send(200, "application/json", buffer);
}

void handleErr() {
  // handle wrong requests
  sprintf(buffer, response, -1, 401);
  server.send(401, "application/json", buffer);
}
 
void setup(void){
  Serial.begin(115200);

  Serial.println("Hello!");
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // if (mdns.begin("kit", WiFi.localIP())) {
  //   Serial.println("MDNS initialized.");
  // }


  server.on("/on", [](){
    if(server.method() == HTTP_GET){
      int relay = server.arg("relay").toInt();
      (relay == 1) ? handleRelay(R1, LOW): (relay == 2) ? handleRelay(R2, LOW) : handleErr();
      Serial.println(buffer);
    }
    else{
      handleErr();
    }
  });

  server.on("/off", [](){
    if(server.method() == HTTP_GET){
      int relay = server.arg("relay").toInt();
      (relay == 1) ? handleRelay(R1, HIGH): (relay == 2) ? handleRelay(R2, HIGH) : handleErr();
      Serial.println(buffer);
    }
    else{
      handleErr();
    }
  });


  server.on("/status", [](){
    if(server.method() == HTTP_GET){
      int relay = server.arg("relay").toInt();
      (relay == 1) ? statusRelay(R1): (relay == 2) ? statusRelay(R2) : handleErr();
      Serial.println(buffer);
    }
    else{
      handleErr();
    }
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server initialized.");
}
 
void loop(void){
  server.handleClient();
} 
