#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <StreamString.h>

#ifndef STASSID
#define STASSID "KKSZKI_V3"
#define STAPSK "erettsegi"
#endif

/* Ide írd a html-t a két zárójel közé! */
const char html[] PROGMEM = R"=====(

)=====";

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", html);
}

// függvények

void led1on() {
  digitalWrite(2, HIGH);
}

void led1off() {
  digitalWrite(2, LOW);
}

void led2on() {
  digitalWrite(16, HIGH);
  }

void led2off() {
  digitalWrite(16, LOW);
  }

void setup(void) {
  pinMode(2,OUTPUT);
  pinMode(16, OUTPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // A server.on() függvénnyel lehet kezelni a kérelmeket.
  // A függvény első paramétere az oldal amire a kérelem megy.
  // Ha arra az oldalra kérelem megy, a függvény második paramétere kerül meghívásra
  // Pl: Ha a led1off-ra megy a kérelem, a led1off függvény:
  // server.on("/led1on", led1on);

  server.on("/", handleRoot);
  server.on("/led1on", led1on);
  server.on("/led1off", led1off);
  server.on("/led2on", led2on);
  server.on("/led2off", led2off);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
};
