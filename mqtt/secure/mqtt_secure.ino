#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
// WLAN Setup
#define WLAN_SSID       ". . ."
#define WLAN_PASS       ". . ."

// MQTT setup
#define MQTT_SERVER      "192.168.1.113"
#define MQTT_PORT        8883
#define MQTT_USERNAME    "pruebas"
#define MQTT_PASS        "pruebas"

// Static IP config
IPAddress ip(192,168,1,40);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

const char* response = "{\"status\": %d, \"code\": %d}";
const int R1 = 12;
const int R2 = 13;
char buffer[50];

const char* fingerprint = "00 7A 11 3D 18 8D 31 2F 7A 92 1B 39 B2 A7 89 5C E9 6D 34 DC";

String commands[] = {"ON", "OFF", "STATUS"};

WiFiClientSecure client;

Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASS);


Adafruit_MQTT_Subscribe relay_one = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/relay_one", MQTT_QOS_1);

Adafruit_MQTT_Subscribe relay_two = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/relay_two", MQTT_QOS_1);

Adafruit_MQTT_Publish responder = Adafruit_MQTT_Publish(&mqtt, "/log");


void handleRelay(int relay, char *data) {
  int level;
  String cmd = data;
  if (cmd == commands[0]){
    level = LOW;
    digitalWrite(relay, level);
  }
  else if (cmd == commands[1]){
    level = HIGH;
    digitalWrite(relay, level);
  }
  else if (cmd == commands[2]){
    level = digitalRead(relay);
  }
  else {
    level = -1;
  }
  level == -1 ? level = -1 : level ? level = 0 : level = 1;


  sprintf(buffer, response, level , 200);
  Serial.println(buffer);
  responder.publish(buffer);
}

void relayCallbackOne(char *data, uint16_t len){
  Serial.print("Relay 1 received: ");
  Serial.println(data);
  handleRelay(R1, data);
}

void relayCallbackTwo(char *data, uint16_t len){
  Serial.print("Relay 2 received: ");
  Serial.println(data);
  handleRelay(R2, data);
}


void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

void verifyFingerprint() {

  const char* host = AIO_SERVER;

  Serial.print("Connecting to ");
  Serial.println(host);

  if (! client.connect(host, AIO_SERVERPORT)) {
    Serial.println("Connection failed. Halting execution.");
    while(1);
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("Connection secure.");
  } else {
    Serial.println("Connection insecure! Halting execution.");
    while(1);
  }

}

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Hello!"));
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  WiFi.config(ip, gateway, subnet);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WLAN_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.verify(fingerprint, MQTT_SERVER)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }
  // verifyFingerprint()
  relay_one.setCallback(relayCallbackOne);
  relay_two.setCallback(relayCallbackTwo);
  
  // Setup MQTT subscription for time feed.
  mqtt.subscribe(&relay_one);
  mqtt.subscribe(&relay_two);

}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(10000);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
